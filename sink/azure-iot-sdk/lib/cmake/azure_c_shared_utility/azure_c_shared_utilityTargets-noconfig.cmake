#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "aziotsharedutil" for configuration ""
set_property(TARGET aziotsharedutil APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(aziotsharedutil PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "C"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libaziotsharedutil.a"
  )

list(APPEND _cmake_import_check_targets aziotsharedutil )
list(APPEND _cmake_import_check_files_for_aziotsharedutil "${_IMPORT_PREFIX}/lib/libaziotsharedutil.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
