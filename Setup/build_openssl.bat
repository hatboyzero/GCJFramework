@echo off

call project_vars.bat

if exist %OPENSSL_SRC% goto :end

set OPENSSL_SNAPSHOT=SNAP-%date:~10,4%%date:~4,2%%date:~7,2%
set OPENSSL_ARCHIVE=openssl-%OPENSSL_VERSION%-stable-%SNAPSHOT%
cd %DEV_DIR%
%WGET% ftp://ftp.openssl.org/snapshot/%OPENSSL_ARCHIVE%.tar.gz
%TAR% -zxvf %OPENSSL_ARCHIVE%.tar.gz
rename %OPENSSL_ARCHIVE% openssl
del %OPENSSL_ARCHIVE%.tar.gz

:end

if not exist %INSTALLS_DIR% mkdir %INSTALLS_DIR%
if not exist %OPENSSL_INSTALL% mkdir %OPENSSL_INSTALL%

cd %OPENSSL_SRC%

for /f "tokens=1-4 delims=[]- " %%a in ('ver') do (set OSVERSION=%%d)
set TARGETCPU=x86
set PLATFORM=x86
echo Windows Version: %OSVERSION%

perl Configure VC-WIN32 --prefix=%OPENSSL_INSTALL%
call ms\do_ms
nmake -f ms\ntdll.mak
nmake -f ms\ntdll.mak install

set PLATFORM=

cd %WORKING_DIR%

@echo on