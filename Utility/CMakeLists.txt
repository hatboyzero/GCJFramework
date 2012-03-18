cmake_minimum_required (VERSION 2.6)

project (GCJUtility)
set (PROJECT_PREFIX "Core")

if (NOT GCJ_PARENT)
	find_path (GCJ_PARENT GCJFramework .. ${CMAKE_CURRENT_SOURCE_DIR}/../.. ../.. ../../.. ENV)
endif (NOT GCJ_PARENT)

set (CMAKE_MODULE_PATH "${GCJ_PARENT}/GCJFramework/CMake/Modules" ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_MODULE_PATH})
list (REMOVE_DUPLICATES CMAKE_MODULE_PATH)

Find_Package(Boost REQUIRED serialization system filesystem)

SET (LIB_TYPE SHARED)

set (GCJUtility_SRC
	Configuration.hpp
	CodeJamLogin.hpp
	ContestManager.hpp
	GoogleLogin.hpp
	src/CodeJamLogin.cpp
	src/ContestManager.cpp
	src/GoogleLogin.cpp
)

set (GCJUtility_DEFINITIONS -DGCJUTILITY_EXPORTS ${GCJ_DEFINITIONS})
add_definitions (${GCJUtility_DEFINITIONS})

include_directories (${Boost_INCLUDE_DIR})

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
