## Build Requirements

### Visual Studio 2022

 * *Community*, *Professional* or *Enterprise* Edition
 * MSVC v143 Buildtools (x64/x86, ARM, ARM64)
 * C++ MFC for latest v143 build tools (x64/x86, ARM, ARM64)
 * C++ ATL for latest v143 build tools (x64/x86, ARM, ARM64)
 * Windows 10 SDK

### How to Build with opencv
 * build opencv in https://github.com/TyrionQu/deployment-pipeline with cmd file: DownloadAndBuildDeps.cmd
 * you can get opencv dll file opencv_world481d.dll in : deployment-pipeline\dependencies\opencv\build\bin\Debug 
 * copy opencv_world481d.dll to currect lib folder