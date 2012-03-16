cmake_minimum_required (VERSION 2.6)

project (Solution-433101-A)
set (PROJECT_PREFIX "Solutions/Contest-433101/Solution-A")

if (NOT GCJ_PARENT)
	find_path (GCJ_PARENT GCJFramework .. ../.. ../../.. ../../../.. ENV)
endif (NOT GCJ_PARENT)

set (CMAKE_MODULE_PATH 
	"${GCJ_PARENT}/GCJFramework/CMake/Modules"
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_MODULE_PATH}
)
list (REMOVE_DUPLICATES CMAKE_MODULE_PATH)

Find_Package (Boost REQUIRED system serialization date_time)

set (LIB_TYPE SHARED)

set (Solution_SRC
	src/Configuration.hpp
	src/Module.hpp
	src/Module.cpp
	src/Solution.hpp
	src/Solution.cpp
)

set (Solution_DEFINITIONS ${GCJFramework_DEFINITIONS} -DSOLUTION_EXPORTS)
add_definitions (${Solution_DEFINITIONS})

include_directories (${GCJ_PARENT} ${Boost_INCLUDE_DIR})

set (Solution_LINK_DIRECTORIES ${Boost_LIBRARY_DIRS})
link_directories (${Solution_LINK_DIRECTORIES})

add_library (Solution-433101-A ${LIB_TYPE} ${Solution_SRC})

add_dependencies (Solution-433101-A GCJCore)

set (Solution_LIBRARIES GCJCore ${Boost_LIBRARIES})
target_link_libraries (Solution-433101-A ${Solution_LIBRARIES})

set_target_properties (Solution-433101-A PROPERTIES DEBUG_POSTFIX "_d")

install ( TARGETS
	Solution-433101-A
	RUNTIME DESTINATION ${GCJ_PARENT}/installs/GCJFramework/bin/solutions
	LIBRARY DESTINATION ${GCJ_PARENT}/installs/GCJFramework/lib/solutions
	ARCHIVE DESTINATION ${GCJ_PARENT}/installs/GCJFramework/lib/solutions
)
