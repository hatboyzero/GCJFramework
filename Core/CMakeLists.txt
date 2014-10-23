cmake_minimum_required (VERSION 2.6)

project (GCJCore)
set (PROJECT_PREFIX "Core")

if (NOT GCJ_PARENT)
	find_path (GCJ_PARENT GCJFramework .. ${CMAKE_CURRENT_SOURCE_DIR}/../.. ../.. ../../.. ENV)
endif (NOT GCJ_PARENT)

set (CMAKE_MODULE_PATH "${GCJ_PARENT}/GCJFramework/CMake/Modules" ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_MODULE_PATH})
list (REMOVE_DUPLICATES CMAKE_MODULE_PATH)

SET (LIB_TYPE SHARED)

set (GCJCore_SRC
	Configuration.hpp
	I_Contest.hpp
	I_Module.hpp
	I_ModuleInfo.hpp
	I_ModuleManager.hpp
	I_ModuleService.hpp
	I_Solution.hpp
	src/I_Contest.cpp
	src/I_Module.cpp
	src/I_ModuleInfo.cpp
	src/I_ModuleManager.cpp
	src/I_ModuleService.cpp
	src/I_Solution.cpp
	src/ModuleInfo.cpp
	src/ModuleInfo.hpp
	src/ModuleManager.cpp
	src/ModuleManager.hpp
	src/ModuleService.cpp
	src/ModuleService.hpp
)

set (GCJCore_DEFINITIONS -DGCJCORE_EXPORTS ${GCJ_DEFINITIONS})
add_definitions (${GCJCore_DEFINITIONS})

include_directories (${BoostSourceDir})

add_library (GCJCore ${LIB_TYPE} ${GCJCore_SRC})

target_link_libraries (GCJCore BoostSerialization BoostSystem BoostFilesystem BoostThread BoostDateTime BoostChrono BoostLog)

set_target_properties (GCJCore PROPERTIES DEBUG_POSTFIX "_d")

install ( TARGETS
	GCJCore
	RUNTIME DESTINATION ${GCJ_PARENT}/installs/GCJFramework/bin
	LIBRARY DESTINATION ${GCJ_PARENT}/installs/GCJFramework/lib
	ARCHIVE DESTINATION ${GCJ_PARENT}/installs/GCJFramework/lib
)
