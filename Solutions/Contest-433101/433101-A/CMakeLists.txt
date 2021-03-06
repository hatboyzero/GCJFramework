cmake_minimum_required (VERSION 2.6)

project (433101-A)
set (PROJECT_PREFIX "Solutions/Contest-433101/433101-A")

if (NOT GCJ_PARENT)
	find_path (GCJ_PARENT GCJFramework .. ../.. ../../.. ../../../.. ENV)
endif (NOT GCJ_PARENT)

set (CMAKE_MODULE_PATH 
	"${GCJ_PARENT}/GCJFramework/CMake/Modules"
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_MODULE_PATH}
)
list (REMOVE_DUPLICATES CMAKE_MODULE_PATH)

set (LIB_TYPE SHARED)

set (Solution_SRC
	src/Configuration.hpp
	src/Module.hpp
	src/Module.cpp
	src/Solution.hpp
	src/Solution.cpp
	src/Solution_impl.cpp
)

set (Solution_DEFINITIONS ${GCJ_DEFINITIONS} -DSOLUTION_EXPORTS)
add_definitions (${Solution_DEFINITIONS})

include_directories (${GCJ_PARENT} ${BoostSourceDir})

add_library (433101-A ${LIB_TYPE} ${Solution_SRC})

add_dependencies (433101-A GCJCore)

set (Solution_LIBRARIES GCJCore BoostSerialization BoostSystem BoostFilesystem)
target_link_libraries (433101-A ${Solution_LIBRARIES})

set_target_properties (433101-A PROPERTIES DEBUG_POSTFIX "_d")

install ( TARGETS
	433101-A
	RUNTIME DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin
	LIBRARY DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin
	ARCHIVE DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin
)
