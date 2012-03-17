cmake_minimum_required (VERSION 2.6)

project (GCJExecutor)
set (PROJECT_PREFIX "Core")

if (NOT GCJ_PARENT)
	find_path (GCJ_PARENT GCJFramework .. ${CMAKE_CURRENT_SOURCE_DIR}/../.. ../.. ../../.. ENV)
endif (NOT GCJ_PARENT)

set (CMAKE_MODULE_PATH "${GCJ_PARENT}/GCJFramework/CMake/Modules" ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_MODULE_PATH})
list (REMOVE_DUPLICATES CMAKE_MODULE_PATH)

Find_Package (Boost REQUIRED serialization system filesystem)
Find_Package (ZLIB REQUIRED)
Find_Package (CURL REQUIRED)
Find_Package (RapidJSON REQUIRED)

set (GCJExecutor_SRC
    src/Environment.cpp
	src/Environment.hpp
    src/main.cpp
	src/SolutionExecutive.cpp
	src/SolutionExecutive.hpp
)

set (GCJExecutor_DEFINITIONS ${GCJ_DEFINITIONS})
add_definitions(${GCJExecutor_DEFINITIONS})

include_directories (${Boost_INCLUDE_DIR} ${GCJ_PARENT} ${ZLIB_INCLUDE_DIRS} ${CURL_INCLUDE_DIRS} ${RapidJSON_INCLUDE_DIRS})

link_directories (${Boost_LIBRARY_DIRS})

add_executable (GCJExecutor ${GCJExecutor_SRC})

add_dependencies (GCJExecutor GCJCore)

set (GCJExecutor_LIBRARIES GCJCore ${Boost_LIBRARIES} ${ZLIB_LIBRARIES} ${CURL_LIBRARIES})
target_link_libraries (GCJExecutor ${GCJExecutor_LIBRARIES})

set_target_properties (GCJExecutor PROPERTIES DEBUG_POSTFIX "_d")

if (MSVC)
configure_file (
    ${GCJ_PARENT}/GCJFramework/Executor/GCJExecutor.vcxproj.user.in
    ${CMAKE_BINARY_DIR}/Executor/GCJExecutor.vcxproj.user
    @ONLY
)
endif (MSVC)

configure_file (
    ${GCJ_PARENT}/GCJFramework/Executor/config.json.in
    ${CMAKE_BINARY_DIR}/Executor/config.json
    @ONLY
)

install ( TARGETS
	GCJExecutor
	RUNTIME DESTINATION ${GCJ_PARENT}/installs/GCJFramework/bin
	LIBRARY DESTINATION ${GCJ_PARENT}/installs/GCJFramework/lib
	ARCHIVE DESTINATION ${GCJ_PARENT}/installs/GCJFramework/lib
)
