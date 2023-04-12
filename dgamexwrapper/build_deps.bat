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

@for %%a in (%*) do @(
  IF "%%a"=="wolfssl" call :wolfssl
  IF "%%a"=="libcurl" call :libcurl
  IF "%%a"=="curl" call :curl
  IF "%%a"=="curlpp" call :curlpp
  IF "%%a"=="detours" call :detours
  IF "%%a"=="sqlitecpp" call :sqlitecpp
  IF "%%a"=="all" call :all
  
)

echo ==============================================
echo ==============================================
echo     Dependencies/Submodules Build Done
echo ==============================================
echo ==============================================
exit /b 0

:all
call :wolfssl
call :libcurl
call :curlpp
call :detours
call :sqlitecpp
exit /b 0


:wolfssl
echo ==============================================
echo Building Wolfssl
echo ==============================================
rem  & rem /DWOLFSSL_SHA512 /DMAX_DH_SZ=1036 /DFP_MAX_BITS=8192 /DDEBUG_WOLFSSL
set _CL_=/MT /DFP_MAX_BITS=8192
echo F|xcopy "libs\curl\projects\wolfssl_options.h" "libs\wolfSSL\cyassl\options.h" /Y
echo F|xcopy "libs\curl\projects\wolfssl_options.h" "libs\wolfSSL\wolfssl\options.h" /Y
msbuild libs/wolfSSL/wolfssl64.sln /t:"wolfssl:Clean;Rebuild" /p:Configuration="Release" /p:Platform="Win32" /p:PlatformToolset="v141_xp" /p:nowarn="MSB8051;D9025" /p:CustomAfterMicrosoftCommonTargets="%rootdir%/libs/curl/projects/wolfssl_override.props" /p:OutDir="%rootdir%/libs/wolfSSL/build/Win32/VC15/LIB Release/" /nologo /verbosity:quiet
exit /b 0

:libcurl
echo ==============================================
echo Building libCURL
echo ==============================================
cd libs/curl/projects
call generate.bat vc15
cd %rootdir%
echo F|xcopy "libs\curl\projects\wolfssl_options.h" "libs\wolfSSL\cyassl\options.h" /Y
echo F|xcopy "libs\curl\projects\wolfssl_options.h" "libs\wolfSSL\wolfssl\options.h" /Y
set _CL_=/MT /DSIZEOF_LONG_LONG=8
msbuild libs/curl/projects/Windows/VC15/lib/libcurl.sln /t:"libcurl:Clean;Rebuild" /p:Configuration="Lib Release - Lib wolfSSL" /p:Platform="Win32" /p:PlatformToolset="v141_xp" /p:nowarn="MSB8051;D9025;C4214" /nologo /verbosity:quiet
exit /b 0

:curl
echo ==============================================
echo Building curl
echo ==============================================
cd libs/curl/projects
call generate.bat vc15
cd %rootdir%
echo F|xcopy "libs\curl\projects\wolfssl_options.h" "libs\wolfSSL\cyassl\options.h" /Y
echo F|xcopy "libs\curl\projects\wolfssl_options.h" "libs\wolfSSL\wolfssl\options.h" /Y
set _CL_=/MT /DSIZEOF_LONG_LONG=8
msbuild libs/curl/projects/Windows/VC15/src/curl.sln /t:"curl:Clean;Rebuild" /p:Configuration="Lib Release - Lib wolfSSL" /p:Platform="Win32" /p:PlatformToolset="v141_xp" /p:nowarn="MSB8051;D9025;C4214" /nologo /verbosity:quiet
exit /b 0

:curlpp
echo ==============================================
echo Building curlpp
echo ==============================================

cd libs/curlpp/
rmdir build /s /q
mkdir build
cd build
set _CL_=/MT
cmake .. -A Win32 -DCURL_LIBRARY="../../curl/build/Win32/VC15/LIB Release - LIB wolfSSL/" -DCURL_INCLUDE_DIR="../../curl/include"
cd %rootdir%
msbuild libs/curlpp/build/curlpp.sln /t:"curlpp_static:Clean;Rebuild" /p:Configuration="Release" /p:Platform="Win32" /p:PlatformToolset="v141_xp" /p:nowarn="MSB8051;D9025;C4244" /nologo /verbosity:quiet
exit /b 0

:detours
echo ==============================================
echo Building Detours
echo ==============================================
cd libs/Detours/src
nmake
cd %rootdir%
exit /b 0

:sqlitecpp
echo ==============================================
echo Building SQLiteCpp
echo ==============================================
cd libs/SQLiteCpp
rmdir build /s /q
mkdir build
cd build
cmake .. -A Win32
cd %rootdir%
set _CL_=/MT
msbuild libs/SQLiteCpp/build/SQLiteCpp.sln /t:"sqlite3:Clean;Rebuild" /p:Configuration="Release" /p:Platform="Win32" /p:PlatformToolset="v141_xp" /p:nowarn="MSB8051;D9025;C4244" /nologo /verbosity:quiet
msbuild libs/SQLiteCpp/build/SQLiteCpp.sln /t:"SQLiteCpp:Clean;Rebuild" /p:Configuration="Release" /p:Platform="Win32" /p:PlatformToolset="v141_xp" /p:nowarn="MSB8051;D9025;C4244" /nologo /verbosity:quiet
exit /b 0