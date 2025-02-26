// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <list>
#include <ctime>
#include <cstdio>

#include "iothub_module_client_ll.h"
#include "iothub_client_options.h"
#include "iothub_message.h"
#include "azure_c_shared_utility/threadapi.h"
#include "azure_c_shared_utility/crt_abstractions.h"
#include "azure_c_shared_utility/platform.h"
#include "azure_c_shared_utility/shared_util_options.h"
#include "iothubtransportmqtt.h"
#include "iothub.h"
#include "time.h"

typedef struct MESSAGE_INSTANCE_TAG
{
    IOTHUB_MESSAGE_HANDLE messageHandle;
    time_t send_time;
} 
MESSAGE_INSTANCE;

size_t messagesReceivedByInputQueue = 0;

static std::list<MESSAGE_INSTANCE*> open_acks = { };

static unsigned char *bytearray_to_str(const unsigned char *buffer, size_t len)
{
    unsigned char *ret = (unsigned char *)malloc(len + 1);
    memcpy(ret, buffer, len);
    ret[len] = '\0';
    return ret;
}

static IOTHUBMESSAGE_DISPOSITION_RESULT InputQueue1Callback(IOTHUB_MESSAGE_HANDLE message, void* userContextCallback)
{
    IOTHUBMESSAGE_DISPOSITION_RESULT result;
    IOTHUB_CLIENT_RESULT clientResult;
    IOTHUB_MODULE_CLIENT_LL_HANDLE iotHubModuleClientHandle = (IOTHUB_MODULE_CLIENT_LL_HANDLE)userContextCallback;

    unsigned const char* messageBody;
    size_t contentSize;

    if (IoTHubMessage_GetByteArray(message, &messageBody, &contentSize) == IOTHUB_MESSAGE_OK)
    {
        messageBody = bytearray_to_str(messageBody, contentSize);
        printf("Received Message [%zu]\r\n Data: [%s]\r\n", 
            messagesReceivedByInputQueue, messageBody);
    }

    result = IOTHUBMESSAGE_ASYNC_ACK; // IOTHUBMESSAGE_ACCEPTED

    MESSAGE_INSTANCE* messageInstance = (MESSAGE_INSTANCE*)malloc(sizeof(MESSAGE_INSTANCE));
    messageInstance->messageHandle = message;
    time_t now;
    time(&now);
    messageInstance->send_time = now;

    open_acks.push_back(messageInstance);

    messagesReceivedByInputQueue++;
    return result;
}

static IOTHUB_MODULE_CLIENT_LL_HANDLE InitializeConnection()
{
    IOTHUB_MODULE_CLIENT_LL_HANDLE iotHubModuleClientHandle;

    if (IoTHub_Init() != 0)
    {
        printf("Failed to initialize the platform.\r\n");
        iotHubModuleClientHandle = NULL;
    }
    else if ((iotHubModuleClientHandle = IoTHubModuleClient_LL_CreateFromEnvironment(MQTT_Protocol)) == NULL)
    {
        printf("ERROR: IoTHubModuleClient_LL_CreateFromEnvironment failed\r\n");
    }
    else
    {
        // Uncomment the following lines to enable verbose logging.
        bool traceOn = true;
        IoTHubModuleClient_LL_SetOption(iotHubModuleClientHandle, OPTION_LOG_TRACE, &traceOn);
    }

    return iotHubModuleClientHandle;
}

static void DeInitializeConnection(IOTHUB_MODULE_CLIENT_LL_HANDLE iotHubModuleClientHandle)
{
    if (iotHubModuleClientHandle != NULL)
    {
        IoTHubModuleClient_LL_Destroy(iotHubModuleClientHandle);
    }
    IoTHub_Deinit();
}

static int SetupCallbacksForModule(IOTHUB_MODULE_CLIENT_LL_HANDLE iotHubModuleClientHandle)
{
    int ret;

    if (IoTHubModuleClient_LL_SetInputMessageCallback(iotHubModuleClientHandle, "input", InputQueue1Callback, (void*)iotHubModuleClientHandle) != IOTHUB_CLIENT_OK)
    {
        printf("ERROR: IoTHubModuleClient_LL_SetInputMessageCallback(\"input\")..........FAILED!\r\n");
        ret = 1;
    }
    else
    {
        ret = 0;
    }

    return ret;
}

void iothub_module()
{
    IOTHUB_MODULE_CLIENT_LL_HANDLE iotHubModuleClientHandle;

    srand((unsigned int)time(NULL));

    if ((iotHubModuleClientHandle = InitializeConnection()) != NULL && SetupCallbacksForModule(iotHubModuleClientHandle) == 0)
    {
        // The receiver just loops constantly waiting for messages.
        printf("Waiting for incoming messages.\r\n");
        while (true)
        {
            IoTHubModuleClient_LL_DoWork(iotHubModuleClientHandle);
            ThreadAPI_Sleep(100);

            // ACK open messages
            time_t now;
            time(&now);

            for (std::list<MESSAGE_INSTANCE_TAG*>::iterator it = open_acks.begin(); it != open_acks.end();)
            {               
               MESSAGE_INSTANCE_TAG* messageInstance = *it;

               int delay = messagesReceivedByInputQueue >= 100 && messagesReceivedByInputQueue < 300 ? 45 : 5;

               if(messageInstance->send_time + delay > now) {
                   printf("ACKing message with delay [%zu]\r\n", delay);

                   if (IOTHUB_CLIENT_OK != IoTHubModuleClient_LL_SendMessageDisposition(iotHubModuleClientHandle, messageInstance->messageHandle, IOTHUBMESSAGE_ACCEPTED)) {
                       IoTHubMessage_Destroy(messageInstance->messageHandle);
                       free(messageInstance);
                    }

                    open_acks.erase(it);
                } else {
                    it++;
                }
            }
        }
    }

    DeInitializeConnection(iotHubModuleClientHandle);
}

int main(void)
{
    std::setbuf(stdout, nullptr);
    std::setbuf(stderr, nullptr);
    printf("Starting...\r\n");

    iothub_module();
    return 0;
}
