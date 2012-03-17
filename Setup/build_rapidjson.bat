@echo off

call project_vars.bat

set RAPIDJSON_VENDOR_DROP=http://rapidjson.googlecode.com/svn/trunk

if exist %RAPIDJSON_SRC% goto pull

svn co %RAPIDJSON_VENDOR_DROP% %RAPIDJSON_SRC%
goto end

:pull
cd %RAPIDJSON_SRC%
svn up

:end

if not exist %INSTALLS_DIR% mkdir %INSTALLS_DIR%
if not exist %RAPIDJSON_INSTALL% mkdir %RAPIDJSON_INSTALL%

xcopy %RAPIDJSON_SRC%\include\rapidjson %RAPIDJSON_INCLUDE%\rapidjson /E /C /I /Q /R /Y

cd %WORKING_DIR%

@echo on