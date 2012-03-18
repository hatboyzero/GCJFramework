@echo off

call build_boost.bat
call build_zlib.bat
call build_openssl.bat
call build_libcurl.bat
call build_rapidjson.bat

@echo on