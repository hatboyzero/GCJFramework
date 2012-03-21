@echo off

call project_vars.bat

set LIBCURL_VENDOR_DROP=git://github.com/bagder/curl.git

if exist %LIBCURL_SRC% goto pull

call git clone %LIBCURL_VENDOR_DROP% %LIBCURL_SRC%
goto end

:pull
cd %LIBCURL_SRC%
call git pull

:end

if not exist %INSTALLS_DIR% mkdir %INSTALLS_DIR%
if not exist %LIBCURL_INSTALL% mkdir %LIBCURL_INSTALL%

cd %LIBCURL_SRC%
call buildconf.bat

cd %LIBCURL_SRC%\winbuild
nmake /f Makefile.vc MODE=dll VC=10 WITH_DEVEL=%ZLIB_INSTALL% WITH_ZLIB=dll WITH_SSL=dll DEBUG=no ENABLE_IDN=no

xcopy %LIBCURL_SRC%\builds\libcurl-release-dll-ssl-dll-zlib--ipv6-sspi\* %LIBCURL_INSTALL% /E /C /I /Q /R /Y

cd %WORKING_DIR%

@echo on