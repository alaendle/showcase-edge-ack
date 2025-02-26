#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "umqtt" for configuration ""
set_property(TARGET umqtt APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(umqtt PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "C"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libumqtt.a"
  )

list(APPEND _cmake_import_check_targets umqtt )
list(APPEND _cmake_import_check_files_for_umqtt "${_IMPORT_PREFIX}/lib/libumqtt.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
