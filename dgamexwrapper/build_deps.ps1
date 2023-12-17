function Build-WolfSSL {
	param (
        $rootdir
    )
	echo '==================='
	echo 'Building WolfSSL...'
	echo '==================='
	$Env:_CL_='/MT'
	Copy-Item -Force -Path ./libs/curl/projects/wolfssl_options.h -Destination ./libs/wolfSSL/cyassl/options.h -Recurse
	Copy-Item -Force -Path ./libs/curl/projects/wolfssl_options.h -Destination ./libs/wolfSSL/wolfssl/options.h -Recurse
	msbuild libs/wolfSSL/wolfssl64.sln /t:'"wolfssl:Clean;Rebuild"' /p:Configuration="Release" /p:Platform="Win32" /p:PlatformToolset="v141_xp" /p:nowarn='"MSB8051;D9025"' /p:CustomAfterMicrosoftCommonTargets="$rootdir/libs/curl/projects/wolfssl_override.props" /p:OutDir="$rootdir/libs/wolfSSL/build/Win32/VC14.10/LIB Release/" /nologo /verbosity:quiet
}

function Build-WolfSSL-Client {
	param (
        $rootdir
    )
	echo '==================='
	echo 'Building WolfSSL Client...'
	echo '==================='
	$Env:_CL_='/MT'
	Copy-Item -Force -Path ./libs/curl/projects/wolfssl_options.h -Destination ./libs/wolfSSL/cyassl/options.h -Recurse
	Copy-Item -Force -Path ./libs/curl/projects/wolfssl_options.h -Destination ./libs/wolfSSL/wolfssl/options.h -Recurse
	msbuild libs/wolfSSL/wolfssl64.sln /t:'"client:Clean;Rebuild"' /p:Configuration="Release" /p:Platform="Win32" /p:PlatformToolset="v141_xp" /p:nowarn='"MSB8051;D9025"' /p:CustomAfterMicrosoftCommonTargets="$rootdir/libs/curl/projects/wolfssl_override.props" /p:OutDir="$rootdir/libs/wolfSSL/build/Win32/VC14.10/LIB Release/" /nologo /verbosity:quiet
}
function Build-libcURL {
	param (
        $rootdir
    )
	echo '==================='
	echo 'Building libcURL...'
	echo '==================='
	if(-Not (Test-Path -Path ./libs/curl/projects/Windows/VC14.10/lib/libcurl.sln -PathType Leaf))
	{
		echo 'Generating project files...'
		cd ./libs/curl/projects
		.\generate.bat vc14.10
	}
	$Env:_CL_='/MT /DCURL_DISABLE_SMB'
	cd $rootdir
	msbuild ./libs/curl/projects/Windows/VC14.10/lib/libcurl.sln /t:'"libcurl:Clean;Rebuild"' /p:Configuration="Lib Release - Lib wolfSSL" /p:Platform="Win32" /p:PlatformToolset="v141_xp" /p:nowarn='"MSB8051;D9025;C4214"' /nologo /verbosity:quiet
}
function Build-cURL {
	param (
        $rootdir
    )
	echo '==================='
	echo 'Building cURL...'
	echo '==================='
	if(-Not (Test-Path -Path ./libs/curl/projects/Windows/VC14.10/src/curl.sln -PathType Leaf))
	{
		echo 'Generating project files...'
		cd ./libs/curl/projects
		.\generate.bat vc14.10
	}
	cd $rootdir
	$Env:_CL_='/MT /DCURL_DISABLE_SMB'
	# build libcurl if it isn't built or it isn't up to date
	echo '==================='
	echo 'Updating libcURL...'
	echo '==================='
	msbuild ./libs/curl/projects/Windows/VC14.10/lib/libcurl.sln /t:'"libcurl"' /p:Configuration="Lib Release - Lib wolfSSL" /p:Platform="Win32" /p:PlatformToolset="v141_xp" /p:nowarn='"MSB8051;D9025;C4214"' /nologo /verbosity:quiet
	echo '==================='
	echo 'Building cURL...'
	echo '==================='
	msbuild ./libs/curl/projects/Windows/VC14.10/src/curl.sln /t:'"curl:Clean;Rebuild"' /p:Configuration="Lib Release - Lib wolfSSL" /p:Platform="Win32" /p:PlatformToolset="v141_xp" /p:nowarn='"MSB8051;D9025;C4214"' /nologo /verbosity:quiet
}
function Build-cURLpp {
	param (
        $rootdir
    )
	echo '==================='
	echo 'Building cURLpp...'
	echo '==================='
	cd ./libs/curlpp/
	if(Test-Path ./build) {Remove-Item ./build -Recurse -Force}
	New-Item ./build -ItemType Directory | Out-Null
	cd ./build
	cmake .. -A Win32 -DCURL_LIBRARY="$rootdir/libs/curl/build/Win32/VC14.10/LIB Release - LIB wolfSSL/libcurl.lib" -DCURL_INCLUDE_DIR="$rootdir/libs/curl/include"
	cd $rootdir
	$Env:_CL_='/MT /DCURL_STATICLIB'
	msbuild libs/curlpp/build/curlpp.sln /t:'"curlpp_static:Clean;Rebuild"' /p:Configuration="Release" /p:Platform="Win32" /p:PlatformToolset="v141_xp" /p:nowarn='"MSB8051;D9025;C4244"' /nologo /verbosity:quiet
}
function Build-detours {
	param (
        $rootdir
    )
	echo '==================='
	echo 'Building detours...'
	echo '==================='
	cd ./libs/Detours/src
	nmake
	cd $rootdir
}
function Build-SQLiteCpp {
	param (
        $rootdir
    )
	echo '==================='
	echo 'Building SQLiteCpp...'
	echo '==================='
	cd ./libs/SQLiteCpp/
	if(Test-Path ./build) {Remove-Item ./build -Recurse -Force}
	New-Item ./build -ItemType Directory | Out-Null
	cd ./build
	cmake .. -A Win32
	cd $rootdir
	$Env:_CL_='/MT'
	msbuild libs/SQLiteCpp/build/SQLiteCpp.sln /t:'"sqlite3:Clean;Rebuild"' /p:Configuration="Release" /p:Platform="Win32" /p:PlatformToolset="v141_xp" /p:nowarn='"MSB8051;D9025;C4244"' /nologo /verbosity:quiet
	msbuild libs/SQLiteCpp/build/SQLiteCpp.sln /t:'"SQLiteCpp:Clean;Rebuild"' /p:Configuration="Release" /p:Platform="Win32" /p:PlatformToolset="v141_xp" /p:nowarn='"MSB8051;D9025;C4244"' /nologo /verbosity:quiet
}

echo '=============================================='
echo '=============================================='
echo 'NightFall Dependencies/Submodules Build Script'
echo '=============================================='
echo '=============================================='
$rootdir = $pwd
$build_all = 'all' -in $Args
if($build_all -or 'wolfssl' -in $Args) {Build-WolfSSL $rootdir}
if($build_all -or 'wolfssl_client' -in $Args) {Build-WolfSSL-Client $rootdir}
if($build_all -or 'libcurl' -in $Args) {Build-libcURL $rootdir}
if($build_all -or 'curl' -in $Args) {Build-cURL $rootdir}
if($build_all -or 'curlpp' -in $Args) {Build-cURLpp $rootdir}
if($build_all -or 'detours' -in $Args) {Build-detours $rootdir}
if($build_all -or 'sqlitecpp' -in $Args) {Build-SQLiteCpp $rootdir}
echo '=============================================='
echo '=============================================='
echo '    Dependencies/Submodules Build Done        '
echo '=============================================='
echo '=============================================='