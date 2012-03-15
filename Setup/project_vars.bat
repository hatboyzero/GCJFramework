REM ***Project Information***

set PROJECT=GCJFramework
set PROJECT_UPPER=GCJFRAMEWORK
set PROJECT_NAME=GCJFramework
set PROJECT_VERSION=0.1.0
set %PROJECT_UPPER%_VERSION=%PROJECT_VERSION%
for /f "tokens=1,2,3 delims=. " %%a in ("%PROJECT_VERSION%") do set PROJECT_MAJOR_VERSION=%%a&set PROJECT_MINOR_VERSION=%%b&set PROJECT_PATCH_VERSION=%%c

REM ***GIT Information***
set PROJECT_REPO=git://hatboyzero@bitbucket.org/hatboyzero/gcjframework.git

REM ***Local Build Environment Paths***
set WORKING_DIR=%CD%
set DEV_DIR=%WORKING_DIR%\..\..
set ROOT_DIR=%DEV_DIR%\..
set BUILDS_DIR=%DEV_DIR%\builds
set INSTALLS_DIR=%DEV_DIR%\installs

REM ***Dependency information***

REM *** Boost ***
set BOOST_VERSION=1.49.0
for /f "tokens=1,2,3 delims=. " %%a in ("%BOOST_VERSION%") do set BOOST_MAJOR_VERSION=%%a&set BOOST_MINOR_VERSION=%%b&set BOOST_PATCH_VERSION=%%c
set BOOST_LOG_VERSION=1.0
for /f "tokens=1,2 delims=. " %%a in ("%BOOST_LOG_VERSION%") do set BOOST_LOG_MAJOR_VERSION=%%a&set BOOST_LOG_MINOR_VERSION=%%b
set BOOST_SRC=%DEV_DIR%\boost-build
set BOOST_INSTALL=%INSTALLS_DIR%\Boost
set BOOST_INCLUDE=%BOOST_INSTALL%\include\boost-%BOOST_MAJOR_VERSION%_%BOOST_MINOR_VERSION%
set BOOST_LIB=%BOOST_INSTALL%\lib
set BOOST_BIN=%BOOST_INSTALL%\lib
set BOOST_THREADING=multi
set BOOST_LINK=shared
set BOOST_RUNTIME=shared
set BOOST_PACKAGES=--with-system --with-serialization --with-filesystem --with-program_options --with-thread --with-date_time --with-regex --with-log

REM *** LibXML2 ***
set LIBXML2_VERSION=2.7.8
for /f "tokens=1,2,3 delims=. " %%a in ("%LIBXML2_VERSION%") do set LIBXML2_MAJOR_VERSION=%%a&set LIBXML2_MINOR_VERSION=%%b&set LIBXML2_PATCH_VERSION=%%c
set LIBXML2_SRC=%DEV_DIR%\libxml2
set LIBXML2_BUILD=%BUILDS_DIR%\libxml2
set LIBXML2_INSTALL=%INSTALLS_DIR%\libxml2
set LIBXML2_INCLUDE=%LIBXML2_INSTALL%\include
set LIBXML2_LIB=%LIBXML2_INSTALL%\lib
set LIBXML2_BIN=%LIBXML2_INSTALL%\bin

REM *** Project settings

set PROJECT_SRC=%DEV_DIR%\%PROJECT_NAME%
set PROJECT_BUILD=%BUILDS_DIR%\%PROJECT_NAME%
set PROJECT_INSTALL=%INSTALLS_DIR%\%PROJECT_NAME%
set PROJECT_INCLUDE=%PROJECT_INSTALL%\include
set PROJECT_LIB=%PROJECT_INSTALL%\lib
set PROJECT_BIN=%PROJECT_INSTALL%\bin
set PROJECT_OPTS=-D BOOST_ROOT=%BOOST_INSTALL% -D BOOST_INCLUDEDIR=%BOOST_INCLUDE%

if [%PATHSET%]==[] set PATH=%PATH%;%PROJECT_SRC%\GnuWin\bin
if [%PATHSET%]==[] set PATHSET=TRUE