@echo off

call project_vars.bat

set LIBXML2_VENDOR_DROP=git://git.gnome.org/libxml2

if exist %LIBXML2_SRC% goto pull

call git clone %LIBXML2_VENDOR_DROP% %LIBXML2_SRC%
cd %LIBXML2_SRC%
call git checkout v%LIBXML2_VERSION%
goto end

:pull
cd %LIBXML2_SRC%
call git pull

:end

if not exist %BUILDS_DIR% mkdir %BUILDS_DIR%
if not exist %LIBXML2_BUILD% mkdir %LIBXML2_BUILD%

if not exist %INSTALLS_DIR% mkdir %INSTALLS_DIR%
if not exist %LIBXML2_INSTALL% mkdir %LIBXML2_INSTALL%

cd %LIBXML2_SRC%\win32
cscript configure.js compiler=msvc prefix=%LIBXML2_INSTALL% iconv=no
nmake /f Makefile clean
nmake /f Makefile
nmake /f Makefile install

cd %WORKING_DIR%

@echo on