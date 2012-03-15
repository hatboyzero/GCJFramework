@echo off

call project_vars.bat

if exist %PROJECT_SRC% goto pull

call git clone %PROJECT_REPO% %PROJECT_SRC%
goto end

:pull
cd %PROJECT_SRC%
call git pull

:end

if not exist %BUILDS_DIR% mkdir %BUILDS_DIR%
if not exist %INSTALLS_DIR% mkdir %INSTALLS_DIR%
if not exist %PROJECT_BUILD% mkdir %PROJECT_BUILD%
if not exist %PROJECT_INSTALL% mkdir %PROJECT_INSTALL%

cd %PROJECT_BUILD%
cmake -G "Visual Studio 10" %PROJECT_OPTS% -D %PROJECT_NAME%_PARENT:PATH=%DEV_DIR% -D CMAKE_INSTALL_PREFIX:PATH=%PROJECT_INSTALL% %PROJECT_SRC%

msbuild %PROJECT_NAME%.sln /m /t:Build /p:Configuration=Debug
msbuild INSTALL.vcxproj /m /p:Configuration=Debug
msbuild %PROJECT_NAME%.sln /m /t:Build /p:Configuration=Release
msbuild INSTALL.vcxproj /m /p:Configuration=Release

cd %WORKING_DIR%

@echo on