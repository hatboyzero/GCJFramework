@echo off

call "%PROGRAMFILES(X86)%\Microsoft Visual Studio 10.0\VC\vcvarsall.bat"" x86
call project_vars.bat

mt -manifest %WORKING_DIR%\patch.manifest.xml -outputresource:"%PROGRAMFILES(X86)%\GnuWin32\bin\patch.exe";1

@echo on