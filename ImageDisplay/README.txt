This is a crossplatform vscode c++ imageDisplay starter project using wxWidgets.
It contains four folders:
	1. src: source code, this is where you should put your code
	2. images: this is the resource folder for images
	3. dependency: this is where the project dependencies reside
	4. manifest: this is where the manifest file resides, it is specifically used for windows

Normally, you don't need to touch the manifest and dependency folders unless you really know what you are doing!

To avoid possible OS compatibility issues, we don't provide pre-compiled binaries for dependencies, but the build script(CMakeLists.txt) has been provided. 

Currently there is only one Main.cpp file in the src folder, you can add more files if you want, but you need to modify the CMakeLists.txt file accordingly.
The main file is well commented, read it and it should be easy to understand how to modify it for your own purpose.

How to build and run?(Note: All ctrl+shift+p commands are for windows and linux, for mac, use cmd+shift+p instead)
1. Open this project in vscode
2. In vscode extensions market, install cmake tools extension, c/c++ Extension Pack, reload or restart the vscode if needed
3. Install cmake, on windows, you can install cmake from https://cmake.org/download/, on mac, you can install cmake using brew, on linux, you can install cmake using apt-get.
	cmake version 3.26.3 or above is recommended. Don't forget to add cmake to your PATH environment variable.
4. Install gcc compiler, on windows, you can install mingw-w64 from https://sourceforge.net/projects/mingw-w64/, 
	on mac, you can install gcc using brew(or clang if you prefer, which should be there open box), on linux, you can install gcc using apt-get.
	gcc version 12.2 or above is recommended. Don't forget to add gcc to your PATH environment variable.
5. in vscode, ctrl+shift+p and input "change configuration provider" to choose cmake as configuration provider, then ctrl+shift+p and input "cmake kit" to select cmake tool kit, then ctrl+shift+p to 
	select c/c++ Edit Configurations(UI), change compiler path and intellisense mode accordingly. Change c standard and c++ standard to c17 and c++17 respectively.
6. ctrl+shift+p and choose cmake:set build target, then choose the target you want to build(here is MyImageApplication), then choose cmake:delete cache and reconfigure(just to make sure all is clean), then choose cmake:build.
	First time build might take a long time, because the dependencies need to be built first, but after that, it should be fast.
7. Rarely, you may want to choose cmake:clean and rebuild, but this would rebuild the whole project, including the dependencies, which may take a long time.
8. In build folder, you will find a MyImageApplication executable file, initially if you want to see something, you are expected to launch it under the build folder,
	as the program uses a relative path to load a image under images folder, but this is just for demonstration purpose.

For Linux users, this starter code is only tested on Ubuntu 22.04 with default gcc compiler.
For windows users, this starter code is only tested on Windows 10 with mingw-w64 gcc 12.2.0 compiler.
For mac users, this starter code is only tested on an Apple Sillicon mac, using Mac OS 13.2.1 with clang 14.0.0 arm64-apple-darwin22.3.0 compiler.

If you got intellisense issue, we recommend you first ctrl+shift+p and choose c/c++: Restart Intellisense for Active File, if this doesn't work,
	you can then try to reset the intellisense databse, and if still doesn't work, you can try to restart vscode. If still does not work, then you may
	got some problems in intellisense configuration.

From my perspective, choosing cmake as the intellisense configuration provider is the best choice to setup intellisense to index dependency headers.