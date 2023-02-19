@echo off
rem You must run this file from inside Developer Command Prompt for Visual Studio
echo ==============================================
echo ==============================================
echo ==============================================
echo NightFall Dependencies/Submodules Build Script
echo ==============================================
echo ==============================================
echo ==============================================
set "rootdir=%cd%"
set _CL_=/MT
echo ==============================================
echo Building Wolfssl
echo ==============================================
msbuild libs/wolfSSL/wolfssl64.sln /t:"wolfssl:Clean;Rebuild" /p:Configuration="Release" /p:Platform="Win32" /p:PlatformToolset="v141_xp" /p:nowarn="MSB8051;D9025" /nologo /verbosity:quiet
echo ==============================================
echo Building libCURL
echo ==============================================
cd libs/curl/projects
call generate.bat vc15
cd %rootdir%
echo F|xcopy "libs\wolfSSL\cyassl\options.h.in" "libs\wolfSSL\cyassl\options.h" /Y
set _CL_=/MT /DSIZEOF_LONG_LONG=8
msbuild libs/curl/projects/Windows/VC15/lib/libcurl.sln /t:"libcurl:Clean;Rebuild" /p:Configuration="Lib Release - Lib wolfSSL" /p:Platform="Win32" /p:PlatformToolset="v141_xp" /p:nowarn="MSB8051;D9025;C4214" /nologo /verbosity:quiet
set _CL_=/MT

echo ==============================================
echo Building curlpp
echo ==============================================

cd libs/curlpp/
rmdir build /s /q
mkdir build
cd build
cmake .. -A Win32 -DCURL_LIBRARY="../../curl/build/Win32/VC15/Lib Release - Lib wolfSSL/" -DCURL_INCLUDE_DIR="../../curl/include"
cd %rootdir%
msbuild libs/curlpp/build/curlpp.sln /t:"curlpp_static:Clean;Rebuild" /p:Configuration="Release" /p:Platform="Win32" /p:PlatformToolset="v141_xp" /p:nowarn="MSB8051;D9025;C4244" /nologo /verbosity:quiet


echo ==============================================
echo Building Detours
echo ==============================================

cd libs/Detours/src
nmake
cd %rootdir%

echo ==============================================
echo Building SQLiteCpp
echo ==============================================
cd libs/SQLiteCpp
rmdir build /s /q
mkdir build
cd build
cmake .. -A Win32
cd %rootdir%
msbuild libs/SQLiteCpp/build/SQLiteCpp.sln /t:"sqlite3:Clean;Rebuild" /p:Configuration="Release" /p:Platform="Win32" /p:PlatformToolset="v141_xp"  /p:nowarn="MSB8051;D9025;C4244" /nologo /verbosity:quiet
msbuild libs/SQLiteCpp/build/SQLiteCpp.sln /t:"SQLiteCpp:Clean;Rebuild" /p:Configuration="Release" /p:Platform="Win32" /p:PlatformToolset="v141_xp" /p:nowarn="MSB8051;D9025;C4244" /nologo /verbosity:quiet
echo ==============================================
echo ==============================================
echo     Dependencies/Submodules Build SUCCESS
echo ==============================================
echo ==============================================