cmake_minimum_required (VERSION 2.6)

project (GCJUtility)
set (PROJECT_PREFIX "Utility")

if (NOT GCJ_PARENT)
	find_path (GCJ_PARENT GCJFramework .. ${CMAKE_CURRENT_SOURCE_DIR}/../.. ../.. ../../.. ENV)
endif (NOT GCJ_PARENT)

set (CMAKE_MODULE_PATH "${GCJ_PARENT}/GCJFramework/CMake/Modules" ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_MODULE_PATH})
list (REMOVE_DUPLICATES CMAKE_MODULE_PATH)

Find_Package(Boost REQUIRED serialization system filesystem)
Find_Package (RapidJSON REQUIRED)

SET (LIB_TYPE SHARED)

set (GCJUtility_SRC
	Configuration.hpp
	I_CodeJamLogin.hpp
	I_ContestManager.hpp
	I_Environment.hpp
	I_GoogleLogin.hpp
	src/CodeJamLogin.hpp
	src/ContestManager.hpp
	src/Environment.hpp
	src/GoogleLogin.hpp
	src/Contest.hpp
	src/Contest.cpp
	src/I_CodeJamLogin.cpp
	src/I_ContestManager.cpp
	src/I_Environment.cpp
	src/I_GoogleLogin.cpp
	src/CodeJamLogin.cpp
	src/ContestManager.cpp
	src/Environment.cpp
	src/GoogleLogin.cpp
)

set (GCJUtility_DEFINITIONS -DGCJUTILITY_EXPORTS ${GCJ_DEFINITIONS})
add_definitions (${GCJUtility_DEFINITIONS})

include_directories (${GCJ_PARENT} ${Boost_INCLUDE_DIR} ${RapidJSON_INCLUDE_DIRS})

link_directories (${Boost_LIBRARY_DIRS})

add_library (GCJUtility ${LIB_TYPE} ${GCJUtility_SRC})

add_dependencies (GCJUtility GCJCore)

target_link_libraries (GCJUtility GCJCore ${Boost_LIBRARIES})

set_target_properties (GCJUtility PROPERTIES DEBUG_POSTFIX "_d")

install ( TARGETS
	GCJUtility
	RUNTIME DESTINATION ${GCJ_PARENT}/installs/GCJFramework/bin
	LIBRARY DESTINATION ${GCJ_PARENT}/installs/GCJFramework/lib
	ARCHIVE DESTINATION ${GCJ_PARENT}/installs/GCJFramework/lib
)
