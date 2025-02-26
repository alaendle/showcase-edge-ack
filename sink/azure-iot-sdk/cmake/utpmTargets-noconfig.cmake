#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "utpm" for configuration ""
set_property(TARGET utpm APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(utpm PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "C"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libutpm.a"
  )

list(APPEND _cmake_import_check_targets utpm )
list(APPEND _cmake_import_check_files_for_utpm "${_IMPORT_PREFIX}/lib/libutpm.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
