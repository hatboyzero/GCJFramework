set WGET="%PROGRAMFILES(X86)%\GnuWin32\bin\wget.exe"
set TAR="%PROGRAMFILES(X86)%\GnuWin32\bin\bsdtar.exe"
set PATCH="%PROGRAMFILES(X86)%\GnuWin32\bin\patch.exe"

if not exist %WGET% echo Please install wget via http://downloads.sourceforge.net/gnuwin32/wget-1.11.4-1-setup.exe

if not exist %TAR% echo Please install tar via http://downloads.sourceforge.net/gnuwin32/libarchive-2.4.12-1-setup.exe

if not exist %PATCH% echo Please install patch via http://gnuwin32.sourceforge.net/downlinks/patch.php -- If you run into UAC issues on Windows 7, run update_patch_manifest.bat as admin.

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

REM *** zlib ***
set ZLIB_SRC=%DEV_DIR%\zlib
set ZLIB_INSTALL=%INSTALLS_DIR%\libcurl_deps
set ZLIB_INCLUDE=%ZLIB_INSTALL%\include
set ZLIB_LIB=%ZLIB_INSTALL%\lib
set ZLIB_BIN=%ZLIB_INSTALL%\bin

REM *** OpenSSL ***
set OPENSSL_VERSION=1.0.0
set OPENSSL_SRC=%DEV_DIR%\openssl
set OPENSSL_INSTALL=%INSTALLS_DIR%\libcurl_deps
set OPENSSL_INCLUDE=%OPENSSL_INSTALL%\include
set OPENSSL_LIB=%OPENSSL_INSTALL%\lib
set OPENSSL_BIN=%OPENSSL_INSTALL%\bin

REM *** libcURL ***
set LIBCURL_SRC=%DEV_DIR%\libcurl
set LIBCURL_INSTALL=%INSTALLS_DIR%\libcurl
set LIBCURL_INCLUDE=%LIBCURL_INSTALL%\include
set LIBCURL_LIB=%LIBCURL_INSTALL%\lib
set LIBCURL_BIN=%LIBCURL_INSTALL%\bin

REM *** rapidjson ***
set RAPIDJSON_REV=64
set RAPIDJSON_SRC=%DEV_DIR%\rapidjson
set RAPIDJSON_INSTALL=%INSTALLS_DIR%\rapidjson
set RAPIDJSON_INCLUDE=%RAPIDJSON_INSTALL%\include

REM *** LibXML2 ***
set LIBXML2_VERSION=2.7.8
for /f "tokens=1,2,3 delims=. " %%a in ("%LIBXML2_VERSION%") do set LIBXML2_MAJOR_VERSION=%%a&set LIBXML2_MINOR_VERSION=%%b&set LIBXML2_PATCH_VERSION=%%c
set LIBXML2_SRC=%DEV_DIR%\libxml2
set LIBXML2_BUILD=%BUILDS_DIR%\libxml2
set LIBXML2_INSTALL=%INSTALLS_DIR%\libxml2
set LIBXML2_INCLUDE=%LIBXML2_INSTALL%\include
set LIBXML2_LIB=%LIBXML2_INSTALL%\lib
set LIBXML2_BIN=%LIBXML2_INSTALL%\bin

REM *** wxWidgets ***
set WX_VERSION=2.9.2
for /f "tokens=1,2,3 delims=. " %%a in ("%WX_VERSION%") do set WX_MAJOR_VERSION=%%a&set WX_MINOR_VERSION=%%b&set WX_PATCH_VERSION=%%c
set WX_SRC=%DEV_DIR%\wxWidgets
set WX_BUILD=%BUILDS_DIR%\wxWidgets
set WX_INSTALL=%INSTALLS_DIR%\wxWidgets
set WX_INCLUDE=%WX_INSTALL%\include
set WX_LIB=%WX_INSTALL%\lib
set WX_BIN=%WX_INSTALL%\bin

REM *** Project settings

set PROJECT_SRC=%DEV_DIR%\%PROJECT_NAME%
set PROJECT_BUILD=%BUILDS_DIR%\%PROJECT_NAME%
set PROJECT_INSTALL=%INSTALLS_DIR%\%PROJECT_NAME%
set PROJECT_INCLUDE=%PROJECT_INSTALL%\include
set PROJECT_LIB=%PROJECT_INSTALL%\lib
set PROJECT_BIN=%PROJECT_INSTALL%\bin
set PROJECT_OPTS=-D BOOST_ROOT=%BOOST_INSTALL% -D BOOST_INCLUDEDIR=%BOOST_INCLUDE%
set PROJECT_OPTS=%PROJECT_OPTS% -D ZLIB_INCLUDE_DIR:PATH=%ZLIB_INCLUDE% -D ZLIB_LIBRARY:FILEPATH=%ZLIB_LIB%\zdll.lib
set PROJECT_OPTS=%PROJECT_OPTS% -D CURL_INCLUDE_DIR:PATH=%LIBCURL_INCLUDE% -D CURL_LIBRARY:FILEPATH=%LIBCURL_LIB%\libcurl.lib
set PROJECT_OPTS=%PROJECT_OPTS% -D RapidJSON_INCLUDE_DIR:PATH=%RAPIDJSON_INCLUDE%
set PROJECT_OPTS=%PROJECT_OPTS% -D wxWidgets_ROOT_DIR:PATH=%WX_SRC%
set PROJECT_OPTS=%PROJECT_OPTS% -D OPENSSL_ROOT_DIR:PATH=%OPENSSL_INSTALL%

if [%PATHSET%]==[] set PATH=%PATH%;%PROJECT_SRC%\GnuWin\bin
if [%PATHSET%]==[] set PATHSET=TRUE