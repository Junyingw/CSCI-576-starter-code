This is a cross-platform C++ imageDisplay starter project using wxWidgets. You can use command line tools
and any editor to work on this project, but the setup instructions that we provided specifically cater
to Visual Studio Code (VS Code) - https://code.visualstudio.com/ which is a cross platform code editor.

It contains three folders:
	1. src: source code, this is where you should put your code
	2. dependency: this is where the project dependencies reside
	3. manifest: this is where the manifest file resides, it is specifically used for windows

Normally, you wouldn't need to touch the manifest and dependency folders unless you really know what you are doing!

To avoid possible OS compatibility issues, we don't provide pre-compiled binaries for dependencies,
but the build script (CMakeLists.txt) has been provided. 

Currently there is only one Main.cpp file in the src folder, you can add more files if you want,
but you need to modify the CMakeLists.txt file accordingly. The main file is well commented,
read it and it should be easy to understand how to modify it for your own purposes.

IMPORTANT

To build and run the project, open the ImageDisplay_C++_cross_platform folder as the root folder
in VS Code. You should not open the parent folder (CSCI-576-starter-code) in VS code if you are
trying to build this C++ project.


Build and Run


1. Install GCC Complier
	
	Windows: You can install mingw-w64 from https://sourceforge.net/projects/mingw-w64/
	Mac: You can install using Homebrew. You may already have clang installed (which is invoked
		when gcc command is run). This should be fine. You can verify this using `gcc --version`.
	Linux: You can install gcc using apt-get (or apt)

	Verify GCC installation by running `gcc --version`. GCC version 12.2 or higher is recommended.
	On Mac, clang version 15.0.0 or higher is recommended
	You may need to add gcc to the PATH environment variable.

2. Install CMake

	Windows: You can install cmake from https://cmake.org/download/
	Mac: You can install using Homebrew
	Linux: You can install using apt-get (or apt)

	Verify CMake installation by running `cmake --version`. CMake version 3.28.1 or higher is recommended.
	You may need to add cmake to the PATH environment variable.

3. Open the project folder in vscode.

4. Install and activate the following vscode extensions from the extensions marketplace.
	https://marketplace.visualstudio.com/

	a. C / C++ for VS Code - https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools
	b. CMake for VS Code - https://marketplace.visualstudio.com/items?itemName=twxs.cmake
	c. CMake Tools - https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools

	Ensure that all these extensions are active. Reload or restart vscode if needed.

5. Configure CMake

	Note: All vscode commands are run from the vscode command palette. To activate the Command Palette,
	Windows / Linux: Ctrl+Shift+P,
 	Mac:  Cmd+Shift+P

	Command Palette > Type in "CMake: Configure" and execute it.
	
	1. Find your compiler installation (gcc or clang) in the options that appear.
	   You may use the [scan for kits] option to scan the device for compiler installations.

	2. If prompted, Choose the correct location for CMakeLists
	   file - ${workspaceFolder}/ImageDisplay_C++_cross_platform/CMakeLists.txt

	At this point, the Configure command should execute and you may see some output in vscode output window.

6. Set up Configuration Provider

	Command Palette > Type in "C/C++: Change Configuration Provider" and run it.
	'CMake Tools' should be an option listed if the previous configure step was successful. Choose that.

	Command Palette > Type in "C/C++: Edit Configurations (UI)" and run it.
	This opens up a UI where you can edit the configurations. 
	
	1. Change compiler path and intellisense mode accordingly.
	2. Change C standard and C++ standard to c17 and c++17 respectively.

7. Build

	Command Palette > Type in "CMake: Set build target" and run it.
	Choose the target you want to build. You may choose MyImageApplication to create an executable
	with that name.

	Command Palette > Type in "CMake: Delete cache and reconfigure" and run it.
	This just cleans up the repository to prepare for a clean rebuild.

	Command Palette > Type in "CMake: Build" and run it.
	
	- Initial build might take some time, because the dependencies need to be built first,
	but later builds should be faster.
	- Rarely, you may want to run "CMake: Clean rebuild", but this would
	rebuild the whole project, including the dependencies, which may take a long time.


8. Run

	- In the /build folder, you will find the executable (MyImageApplication).
	- To run this, navigate to the build folder in a terminal and run the executable file.
	- The given starter code takes exactly one argument - a file path to a 512x512 rgb image file
	- This should be invoked as ./MyImageApplication '<path to rgb file>'
	- Example - ./MyImageApplication '../../Lena_512_512.rgb'

9. Rebuilds

	After making changes to the source code, you need to build the executable again.
	Command Palette > Type in "CMake: Build" and run it.

	On restarting vscode, you may need to configure CMake by running "CMake: Configure"
	After that, continue building using "CMake: Build".



For Linux users, this starter code is only tested on Ubuntu 22.04 with default gcc compiler.
For windows users, this starter code is only tested on Windows 10 with mingw-w64 gcc 12.2.0 compiler.
For mac users, this starter code is tested on an Apple Silicon mac, using Mac OS 13.4.1 with clang version 14.0.3 (clang-1403.0.22.14.1) compiler.

If you run into intellisense issues, we recommend the following steps.
	1. Command Palette > Type in "C/C++: Restart IntelliSense for Active File" and run it
	2. If it still doesn't work, you can try to reset the intellisense database.
	3. If still doesn't work, you can try to restart vscode.
	4. If still does not work, then you may have some problems in intellisense configuration.

From my perspective, choosing cmake as the intellisense configuration provider is the best choice
to setup intellisense to index dependency headers.