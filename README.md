# Template - OpenGL - C++

## Install

### Ubuntu
Development Dependencies:
```
libxi-dev
libxinerama-dev
libxcursor-dev
libglew-dev
libxrandr-dev
xorg-dev
```

## Start Projects
```
cd template-opengl
rm -rf .git             # Remove template git repo
rm .gitmodules          # Will be auto created by new repo
git init
git submodule add https://github.com/omniavinco/glew-cmake lib/glew
git submodule add https://github.com/glfw/glfw lib/glfw
cat .gitmodules         # Check if modules are installed
```

## Build

### Load Dependencies
```
git submodule init
git submodule update
```

### CMake
```
mkdir build
cd build
cmake ..
./main
```
