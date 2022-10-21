# Standard FIND_PACKAGE module for libuv, sets the following variables:
#   - JSON-C_FOUND
#   - JSON-C_INCLUDE_DIRS (only if JSON-C_FOUND)
#   - JSON-C_LIBRARIES (only if JSON-C_FOUND)

# Try to find the header
find_path(JSON-C_INCLUDE_DIR json.h PATH_SUFFIXES json-c json)

# Try to find the library
find_library(JSON-C_LIBRARY NAMES json-c libjson-c)

# Handle the QUIETLY/REQUIRED arguments, set JSON-C_FOUND if all variables are
# found
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(JSON-C
                                  REQUIRED_VARS
                                  JSON-C_LIBRARY
                                  JSON-C_INCLUDE_DIR)

# Hide internal variables
mark_as_advanced(JSON-C_INCLUDE_DIR JSON-C_LIBRARY)

# Set standard variables
IF(JSON-C_FOUND)
    set(JSON-C_INCLUDE_DIRS "${JSON-C_INCLUDE_DIR}")
    set(JSON-C_LIBRARIES "${JSON-C_LIBRARY}")
ENDIF()
