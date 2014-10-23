cmake_minimum_required (VERSION 2.6)

project (GCJFramework)

set (GCJFramework_VERSION_MAJOR "0")
set (GCJFramework_VERSION_MINOR "1")
set (GCJFramework_VERSION_PATCH "0")
set (GCJFramework_VERSION "${GCJFramework_VERSION_MAJOR}.${GCJFramework_VERSION_MINOR}.${GCJFramework_VERSION_PATCH}")

set (Boost_ADDITIONAL_VERSIONS "1.57" "1.57.0" "1.56" "1.56.0" "1.55" "1.55.0" "1.54" "1.54.0" "1.53" "1.53.0" "1.52" "1.52.0" "1.51" "1.51.0" "1.50" "1.50.0" "1.49" "1.49.0" "1.48" "1.48.0" "1.47" "1.47.0" "1.46" "1.46.0" "1.45" "1.45.0" "1.44" "1.44.0" "1.43" "1.43.0" "1.42" "1.42.0" "1.41" "1.41.0" "1.40" "1.40.0" "1.39" "1.39.0" "1.38" "1.38.0" "1.37" "1.37.0")

# Attempt to guess the compiler suffix
# NOTE: this is not perfect yet, if you experience any issues
# please report them and use the GCJ_COMPILER variable
# to work around the problems.
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel"
	OR "${CMAKE_CXX_COMPILER}" MATCHES "icl"
	OR "${CMAKE_CXX_COMPILER}" MATCHES "icpc")
  if(WIN32)
	set (GCJ_COMPILER "-iw")
  else()
	set (GCJ_COMPILER "-il")
  endif()
elseif (MSVC13)
  set(GCJ_COMPILER "-vc130")
elseif (MSVC12)
  set(GCJ_COMPILER "-vc120")
elseif (MSVC11)
  set(GCJ_COMPILER "-vc110")
elseif (MSVC10)
  set(GCJ_COMPILER "-vc100")
elseif (MSVC90)
  set(GCJ_COMPILER "-vc90")
elseif (MSVC80)
  set(GCJ_COMPILER "-vc80")
elseif (MSVC71)
  set(GCJ_COMPILER "-vc71")
elseif (MSVC70) # Good luck!
  set(GCJ_COMPILER "-vc7") # yes, this is correct
elseif (MSVC60) # Good luck!
  set(GCJ_COMPILER "-vc6") # yes, this is correct
elseif (BORLAND)
  set(GCJ_COMPILER "-bcb")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "SunPro")
  set(GCJ_COMPILER "-sw")
elseif (MINGW)
  if(${GCJ_MAJOR_VERSION}.${GCJ_MINOR_VERSION} VERSION_LESS 1.34)
	  set(GCJ_COMPILER "-mgw") # no GCC version encoding prior to 1.34
  else()
	_GCJ_COMPILER_DUMPVERSION(GCJ_COMPILER_VERSION)
	set(GCJ_COMPILER "-mgw${GCJ_COMPILER_VERSION}")
  endif()
elseif (UNIX)
  if (CMAKE_COMPILER_IS_GNUCXX)
	if(${GCJ_MAJOR_VERSION}.${GCJ_MINOR_VERSION} VERSION_LESS 1.34)
	  set(GCJ_COMPILER "-gcc") # no GCC version encoding prior to 1.34
	else()
	  _GCJ_COMPILER_DUMPVERSION(GCJ_COMPILER_VERSION)
	  # Determine which version of GCC we have.
	  if(APPLE)
		if(GCJ_MINOR_VERSION)
		  if(${GCJ_MINOR_VERSION} GREATER 35)
			# In GCJ 1.36.0 and newer, the mangled compiler name used
			# on Mac OS X/Darwin is "xgcc".
			set(GCJ_COMPILER "-xgcc${GCJ_COMPILER_VERSION}")
		  else(${GCJ_MINOR_VERSION} GREATER 35)
			# In GCJ <= 1.35.0, there is no mangled compiler name for
			# the Mac OS X/Darwin version of GCC.
			set(GCJ_COMPILER "")
		  endif(${GCJ_MINOR_VERSION} GREATER 35)
		else(GCJ_MINOR_VERSION)
		  # We don't know the GCJ version, so assume it's
		  # pre-1.36.0.
		  set(GCJ_COMPILER "")
		endif(GCJ_MINOR_VERSION)
	  else()
		set(GCJ_COMPILER "-gcc${GCJ_COMPILER_VERSION}")
	  endif()
	endif()
  endif (CMAKE_COMPILER_IS_GNUCXX)
endif()
if(GCJ_DEBUG)
  message(STATUS "[ ${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE} ] "
	"guessed GCJ_COMPILER = ${GCJ_COMPILER}")
endif()

#======================
# Systematically build up the Boost ABI tag
# http://boost.org/doc/libs/1_41_0/more/getting_started/windows.html#library-naming
set( _boost_RELEASE_ABI_TAG "-")
set( _boost_DEBUG_ABI_TAG   "-")
# Key       Use this library when:
#  s        linking statically to the C++ standard library and
#           compiler runtime support libraries.
if(Boost_USE_STATIC_RUNTIME)
set( _boost_RELEASE_ABI_TAG "${_boost_RELEASE_ABI_TAG}s")
set( _boost_DEBUG_ABI_TAG   "${_boost_DEBUG_ABI_TAG}s")
endif()
#  g        using debug versions of the standard and runtime
#           support libraries
if(WIN32)
	if(MSVC OR "${CMAKE_CXX_COMPILER}" MATCHES "icl"
			OR "${CMAKE_CXX_COMPILER}" MATCHES "icpc")
		set(_boost_DEBUG_ABI_TAG "${_boost_DEBUG_ABI_TAG}g")
	endif()
endif()
#  y        using special debug build of python
if(Boost_USE_DEBUG_PYTHON)
	set(_boost_DEBUG_ABI_TAG "${_boost_DEBUG_ABI_TAG}y")
endif()
#  d        using a debug version of your code
set(_boost_DEBUG_ABI_TAG "${_boost_DEBUG_ABI_TAG}d")
#  p        using the STLport standard library rather than the
#           default one supplied with your compiler
if(Boost_USE_STLPORT)
	set( _boost_RELEASE_ABI_TAG "${_boost_RELEASE_ABI_TAG}p")
	set( _boost_DEBUG_ABI_TAG   "${_boost_DEBUG_ABI_TAG}p")
endif()
#  n        using the STLport deprecated "native iostreams" feature
if(Boost_USE_STLPORT_DEPRECATED_NATIVE_IOSTREAMS)
	set( _boost_RELEASE_ABI_TAG "${_boost_RELEASE_ABI_TAG}n")
	set( _boost_DEBUG_ABI_TAG   "${_boost_DEBUG_ABI_TAG}n")
endif()

option (Boost_USE_MULTITHREADED "Use multithreaded Boost libraries" TRUE)
set (_boost_MULTITHREADED "-mt")
if( NOT Boost_USE_MULTITHREADED )
	set (_boost_MULTITHREADED "")
endif()
if(GCJ_DEBUG)
message(STATUS "[ ${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE} ] "
  "_boost_MULTITHREADED = ${_boost_MULTITHREADED}")
endif()

if (WIN32)
	set (BUILD_EXE_TYPE "WIN32")
	set (GCJ_DEFINITIONS "-D_CRT_SECURE_NO_WARNINGS -DUNICODE -D_UNICODE")
	
	if (MSVC)
		set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
	endif (MSVC)
endif (WIN32)

if (NOT GCJ_PARENT)
	find_path (GCJ_PARENT GCJFramework .. ${CMAKE_CURRENT_SOURCE_DIR}/../.. ../.. ../../.. ENV)
endif (NOT GCJ_PARENT)

set (CMAKE_MODULE_PATH "${GCJ_PARENT}/GCJFramework/CMake/Modules" ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_MODULE_PATH})
list (REMOVE_DUPLICATES CMAKE_MODULE_PATH)

include(Utils)
utils_get_target_architecture()

Message("Architecture: ${TargetArchitecture}")

set (GCJ_PROJECTS
	external
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
	"${GCJ_PARENT}/GCJFramework/license.txt"
	DESTINATION
	./
)

install (FILES
	"${GCJ_PARENT}/GCJFramework/license.txt"
	DESTINATION
	"${CMAKE_INSTALL_PREFIX}"
)

if (WIN32)
install (FILES
	"${Boost_LIBRARY_DIRS}/boost_date_time${GCJ_COMPILER}${_boost_MULTITHREADED}${_boost_RELEASE_ABI_TAG}${Boost_LIB_VERSION}.dll"
	"${Boost_LIBRARY_DIRS}/boost_date_time${GCJ_COMPILER}${_boost_MULTITHREADED}${_boost_DEBUG_ABI_TAG}-${Boost_LIB_VERSION}.dll"
	"${Boost_LIBRARY_DIRS}/boost_filesystem${GCJ_COMPILER}${_boost_MULTITHREADED}${_boost_RELEASE_ABI_TAG}${Boost_LIB_VERSION}.dll"
	"${Boost_LIBRARY_DIRS}/boost_filesystem${GCJ_COMPILER}${_boost_MULTITHREADED}${_boost_DEBUG_ABI_TAG}-${Boost_LIB_VERSION}.dll"
	"${Boost_LIBRARY_DIRS}/boost_log${GCJ_COMPILER}${_boost_MULTITHREADED}${_boost_RELEASE_ABI_TAG}${Boost_LIB_VERSION}.dll"
	"${Boost_LIBRARY_DIRS}/boost_log${GCJ_COMPILER}${_boost_MULTITHREADED}${_boost_DEBUG_ABI_TAG}-${Boost_LIB_VERSION}.dll"
	"${Boost_LIBRARY_DIRS}/boost_program_options${GCJ_COMPILER}${_boost_MULTITHREADED}${_boost_RELEASE_ABI_TAG}${Boost_LIB_VERSION}.dll"
	"${Boost_LIBRARY_DIRS}/boost_program_options${GCJ_COMPILER}${_boost_MULTITHREADED}${_boost_DEBUG_ABI_TAG}-${Boost_LIB_VERSION}.dll"
	"${Boost_LIBRARY_DIRS}/boost_system${GCJ_COMPILER}${_boost_MULTITHREADED}${_boost_RELEASE_ABI_TAG}${Boost_LIB_VERSION}.dll"
	"${Boost_LIBRARY_DIRS}/boost_system${GCJ_COMPILER}${_boost_MULTITHREADED}${_boost_DEBUG_ABI_TAG}-${Boost_LIB_VERSION}.dll"
	"${Boost_LIBRARY_DIRS}/boost_thread${GCJ_COMPILER}${_boost_MULTITHREADED}${_boost_RELEASE_ABI_TAG}${Boost_LIB_VERSION}.dll"
	"${Boost_LIBRARY_DIRS}/boost_thread${GCJ_COMPILER}${_boost_MULTITHREADED}${_boost_DEBUG_ABI_TAG}-${Boost_LIB_VERSION}.dll"
	"${OPENSSL_ROOT_DIR}/bin/libeay32.dll"
	"${OPENSSL_ROOT_DIR}/bin/ssleay32.dll"
	"${ZLIB_INCLUDE_DIR}/../bin/zlib.dll"
	"${CURL_INCLUDE_DIR}/../lib/libcurl.dll"
	"${CURL_INCLUDE_DIR}/../bin/cacert.pem"
	DESTINATION
	"${CMAKE_INSTALL_PREFIX}/bin"
)
endif (WIN32)

include (Packaging)