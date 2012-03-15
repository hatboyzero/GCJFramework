cmake_minimum_required (VERSION 2.6)

project (GCJGenerator)
set (PROJECT_PREFIX "Core")

if (NOT GCJ_PARENT)
	find_path (GCJ_PARENT GCJFramework .. ${CMAKE_CURRENT_SOURCE_DIR}/../.. ../.. ../../.. ENV)
endif (NOT GCJ_PARENT)

set (CMAKE_MODULE_PATH "${GCJ_PARENT}/GCJFramework/CMake/Modules" ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_MODULE_PATH})
list (REMOVE_DUPLICATES CMAKE_MODULE_PATH)

Find_Package(Boost REQUIRED serialization system filesystem)

set (GCJGenerator_SRC
    src/main.cpp
)

set (GCJGenerator_DEFINITIONS ${GCJ_DEFINITIONS})
add_definitions(${GCJGenerator_DEFINITIONS})

include_directories (${Boost_INCLUDE_DIR} ${GCJ_PARENT})

link_directories (${Boost_LIBRARY_DIRS})

add_executable (GCJGenerator ${GCJGenerator_SRC})

add_dependencies (GCJGenerator GCJCore)

set (GCJGenerator_LIBRARIES GCJCore ${Boost_LIBRARIES})
target_link_libraries (GCJGenerator ${GCJGenerator_LIBRARIES})

set_target_properties (GCJGenerator PROPERTIES DEBUG_POSTFIX "_d")

if (MSVC)
#configure_file (
#    ${GCJ_PARENT}/GCJFramework/Generator/GCJGenerator.vcxproj.user.in
#    ${CMAKE_BINARY_DIR}/Generator/GCJGenerator.vcxproj.user
#    @ONLY
#)
endif (MSVC)

configure_file (
    ${GCJ_PARENT}/GCJFramework/Generator/config.xml.in
    ${GCJ_PARENT}/GCJFramework/Generator/config.xml
    @ONLY
)

install (TARGETS
    GCJGenerator
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

