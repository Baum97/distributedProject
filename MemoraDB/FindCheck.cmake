# FindCheck.cmake

# Check if pkg-config is available
find_package(PkgConfig)

# If available, use pkg-config to find Check
if(PKG_CONFIG_FOUND)
  pkg_check_modules(PC_CHECK QUIET check)
endif()

# Set search paths for Check
find_path(CHECK_INCLUDE_DIRS NAMES check.h
          PATHS ${PC_CHECK_INCLUDE_DIRS}
          PATH_SUFFIXES check)

find_library(CHECK_LIBRARIES NAMES check
             PATHS ${PC_CHECK_LIBRARY_DIRS})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Check DEFAULT_MSG CHECK_LIBRARIES CHECK_INCLUDE_DIRS)

mark_as_advanced(CHECK_INCLUDE_DIRS CHECK_LIBRARIES)
