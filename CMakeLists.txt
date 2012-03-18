cmake_minimum_required (VERSION 2.6)

project (GCJFramework)

set (GCJFramework_VERSION_MAJOR "0")
set (GCJFramework_VERSION_MINOR "1")
set (GCJFramework_VERSION_PATCH "0")
set (GCJFramework_VERSION "${GCJFramework_VERSION_MAJOR}.${GCJFramework_VERSION_MINOR}.${GCJFramework_VERSION_PATCH}")

set (Boost_ADDITIONAL_VERSIONS "1.49" "1.49.0" "1.48" "1.48.0" "1.47" "1.47.0" "1.46" "1.46.0" "1.45" "1.45.0" "1.44" "1.44.0" "1.43" "1.43.0" "1.42" "1.42.0" "1.41" "1.41.0" "1.40" "1.40.0" "1.39" "1.39.0" "1.38" "1.38.0" "1.37" "1.37.0")
Find_Package (Boost REQUIRED)

if (WIN32)
	set (BUILD_EXE_TYPE "WIN32")
	set (GCJ_DEFINITIONS "-D_CRT_SECURE_NO_WARNINGS -DBOOST_ALL_DYN_LINK -DUNICODE -D_UNICODE")
	
	if (MSVC)
		set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
	endif (MSVC)
endif (WIN32)

if (NOT GCJ_PARENT)
	find_path (GCJ_PARENT GCJFramework .. ${CMAKE_CURRENT_SOURCE_DIR}/../.. ../.. ../../.. ENV)
endif (NOT GCJ_PARENT)

set (CMAKE_MODULE_PATH "${GCJ_PARENT}/GCJFramework/CMake/Modules" ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_MODULE_PATH})
list (REMOVE_DUPLICATES CMAKE_MODULE_PATH)

set (GCJ_PROJECTS
	Core
	Utility
	Executor
	Generator
	Solutions
)

foreach (PROJECT_PATH ${GCJ_PROJECTS})
	message ("-- ${PROJECT_PATH}")
	add_subdirectory ("${GCJ_PARENT}/GCJFramework/${PROJECT_PATH}" "${PROJECT_PATH}")
endforeach (PROJECT_PATH)

install (FILES
	"${GCJ_PARENT}/GCJFramework/Setup/Package/license.txt"
	DESTINATION
	./
)

install (FILES
	"${GCJ_PARENT}/GCJFramework/Setup/Package/license.txt"
	DESTINATION
	"${GCJ_PARENT}/installs/GCJFramework"
)

include (Packaging)