@echo off

call project_vars.bat

set WX_VENDOR_DROP=http://svn.wxwidgets.org/svn/wx/wxWidgets/tags/WX_%WX_MAJOR_VERSION%_%WX_MINOR_VERSION%_%WX_PATCH_VERSION%

if not exist %WX_SRC% call svn co %WX_VENDOR_DROP% %WX_SRC%
if exist %WX_SRC% svn up %WX_SRC%

if not exist %BUILDS_DIR% mkdir %BUILDS_DIR%
if not exist %WX_BUILD% mkdir %WX_BUILD%

if not exist %INSTALLS_DIR% mkdir %INSTALLS_DIR%
if not exist %WX_INSTALL% mkdir %WX_INSTALL%

cd %WX_SRC%\build\msw

nmake /f makefile.vc clean
nmake /f makefile.vc

cd %WORKING_DIR%

@echo on