@echo off

call project_vars.bat

set BOOST_VENDOR_DROP=http://svn.boost.org/svn/boost/tags/release/Boost_%BOOST_MAJOR_VERSION%_%BOOST_MINOR_VERSION%_%BOOST_PATCH_VERSION%

if not exist %BOOST_SRC% svn co %BOOST_VENDOR_DROP% %BOOST_SRC%
if exist %BOOST_SRC% svn up %BOOST_SRC%

call build_boost-log.bat

cd %BOOST_SRC%
call bootstrap.bat
b2 -j%NUMBER_OF_PROCESSORS% debug release threading=%BOOST_THREADING% link=%BOOST_LINK% runtime-link=%BOOST_RUNTIME% %BOOST_PACKAGES% --prefix=%BOOST_INSTALL% install
cd %WORKING_DIR%

@echo on