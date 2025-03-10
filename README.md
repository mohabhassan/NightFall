

# NightFall - (d)gamexwrapper
MOHAA/MOHSH/MOHBT (d)gamex86 wrapper based on the old MOHAA gamex86 wrapper.

NightFall serves a wrapper that compliments various aspects of MOHAA's script engine capabilities.


This is the best public version out there.

Questions are welcomed.

For enhancements and bug reports: [submit an issue](https://github.com/mohabhassan/NightFall/issues).

If you have any fixes/modifications, please submit a PR.

## Downloading
You can download latest version from [here](https://github.com/mohabhassan/NightFall/releases).

## Installation
 - [Installing NightFall](docs/installing.md)

## Documentation

 - [NightFall Documentation](docs/readme.md)

## Building
 - Clone this repo
 - `cd NightFall`
 - `git submodule update --init`
 - Use Visual Studio 2019
 - Start VS2019 Developer PowerShell
 - `cd dgamexwrapper`
 - `build_deps.bat all` to build dependencies, you can also build specific dependencies: `build_deps.bat wolfssl curl libcurl`
 - Build NightFall using `dgamexwrapper.sln` (use any configuration other than Debug)
 
 
## FAQ

 - **What is currently supported ?**
 
 Currently, most reborn functions are supported, some security related additions are not implemented.
 
 - **Will feature xxxx be implemented ?**
 
 [Create an issue](https://github.com/mohabhassan/NightFall/issues) (feature request), I'm more than welcome to add any new features to NightFall!
 
# Contributors
## Main Developer
 - **RyBack**
 

Have fun ! ;)

