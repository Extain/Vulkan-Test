if not exist build mkdir build
cd build
cmake -S ../ -B . -G "MinGW Makefiles"
mingw32-make.exe && mingw32-make.exe Shaders
cd ..
xcopy .\shaders\*.spv .\build\assets
xcopy .\assets\*.* .\build\assets