set ( CPACK_PACKAGE_VERSION ${GCJFramework_VERSION} )
set ( CPACK_PACKAGE_VERSION_MAJOR ${GCJFramework_VERSION_MAJOR} )
set ( CPACK_PACKAGE_VERSION_MINOR ${GCJFramework_VERSION_MINOR} )
set ( CPACK_PACKAGE_VERSION_PATCH ${GCJFramework_VERSION_PATCH} )

set ( CPACK_INSTALL_CMAKE_PROJECTS "${GCJFramework_BINARY_DIR}" "GCJFramework" "ALL" "/" )
set ( CPACK_PACKAGE_DESCRIPTION_SUMMARY "Google Code Jam Solution Framework" )
set ( CPACK_PACKAGE_INSTALL_DIRECTORY "GCJFramework" )
set ( CPACK_PACKAGE_NAME "GCJFramework" )
set ( CPACK_PACKAGE_VENDOR "matthewalangray.com" )

set ( CPACK_RESOURCE_FILE_LICENSE "${GCJ_PARENT}/GCJFramework/license.txt" )
set ( CPACK_PACKAGE_ICON "${GCJ_PARENT}/GCJFramework/Setup/Package/gcjframework.ico" )

set ( CPACK_PACKAGE_CONTACT "Matthew Alan Gray <matthew.alan.gray@gmail.com>" )

set ( CPACK_NSIS_EXTRA_INSTALL_COMMANDS "WriteRegStr \\\${WriteEnvStr_RegKey} \\\"GCJFramework_HOME\\\" $INSTDIR" )

include(CPack)