#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "uhttp" for configuration ""
set_property(TARGET uhttp APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(uhttp PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "C"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libuhttp.a"
  )

list(APPEND _cmake_import_check_targets uhttp )
list(APPEND _cmake_import_check_files_for_uhttp "${_IMPORT_PREFIX}/lib/libuhttp.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
