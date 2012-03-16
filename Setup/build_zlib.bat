@echo off

call project_vars.bat

set ZLIB_VENDOR_DROP=https://gforge.sci.utah.edu/svn/zlib

if exist %ZLIB_SRC% goto pull

svn co %ZLIB_VENDOR_DROP% %ZLIB_SRC%
goto end

:pull
svn up %ZLIB_SRC%

:end

if not exist %INSTALLS_DIR% mkdir %INSTALLS_DIR%
if not exist %ZLIB_INSTALL% mkdir %ZLIB_INSTALL%

cd %ZLIB_SRC%
nmake -f win32\Makefile.msc
xcopy zlib.h %ZLIB_INSTALL%\include\zlib.h /C /Q /R /Y
xcopy zconf.h %ZLIB_INSTALL%\include\zconf.h /C /Q /R /Y
xcopy zlib.lib %ZLIB_INSTALL%\lib\zlib.lib /C /Q /R /Y
xcopy zlib1.dll %ZLIB_INSTALL%\bin\zlib1.dll /C /Q /R /Y
xcopy zlib1.res %ZLIB_INSTALL%\lib\zlib1.res /C /Q /R /Y
xcopy zdll.lib %ZLIB_INSTALL%\lib\zdll.lib /C /Q /R /Y

cd %WORKING_DIR%

@echo on