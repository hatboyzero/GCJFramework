# - Find RapidJSON
# Find the RapidJSON includes.
# Once done, this will define
#
#   RapidJSON_INCLUDE_DIRS  - where to find the RapidJSON headers.
#   RapidJSON_FOUND         - True if RapidJSON is found.
#

FIND_PATH (RapidJSON_INCLUDE_DIR rapidjson)

INCLUDE (${CMAKE_CURRENT_LIST_DIR}/FindPackageHandleStandardArgs.cmake)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(RapidJSON REQUIRED_VARS RapidJSON_INCLUDE_DIR)

IF (RAPIDJSON_FOUND)
    SET (RapidJSON_INCLUDE_DIRS ${RapidJSON_INCLUDE_DIR})
ENDIF (RAPIDJSON_FOUND)