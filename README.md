# CSCI-576-starter-code

This repository contains the starter code for the assignments and projects for CSCI 576 - Multimedia Systems. The starter code just reads pixel data from an rgb image file and displays the image. This repo comprises 3 independent sub-folders. You'll most likely use just one subfolder based on your platform and choice of programming language and. Each subfolder has a readme that describe how to setup the project. 

1. ImageDisplay_C++_cross_platform - This folder contains a C++ project that uses WxWidgets library to display an image. This project is cross-platform and works on Windows, Linux and Mac. Since this project has a dependency on external libraries, we have included a make script that builds the project. Although, it might take a few additional steps to set this up, we recommend that you use this project if you like to use C++ to work on the assignments. At the moment, we have more TA support for this project compared to the other (Windows only) C++ project.

    You can use command line tools and any editor to work on this project, but the setup instructions that we provided specifically cater to [Visual Studio Code (VS Code)](https://code.visualstudio.com/) which is a cross platform code editor.

2. ImageDisplay_C++_windows - This folder contains the starter code for a C++ project built using [Visual Studio IDE](https://visualstudio.microsoft.com/) and works ONLY on Windows. Note that this is different from Visual Studio Code (VS Code) mentioned above. Project specific instructions are available in the Readme file in the subfolder.

3. ImageDisplay_Java - This project contains the starter code implemented in Java. This project is cross-platform and can be run on Windows, Linux or Mac. You can use any editor or command line tools to work on this project.

## RGB File Format

All three starter code projects, currently expect a 512x512 RGB data file as input. In each of the three projects the dimensions are specified at one location in code. Changing the dimension here lets you read and display images of different dimensions.

The file should be a stream of bytes where each byte stores a value between 0 and 255. The RGB values are arranged RRRRRR.....GGGGGG.....BBBBB i.e the R values of all the pixels followed by the G values of all the pixels followed by the B values of all pixels. The values are NOT arranged as RGB.RGB.RGB and so on.

## Acknowledgment

Thanks to Rui Zhu and Yuyang Huang for their contributions to the original starter code.
