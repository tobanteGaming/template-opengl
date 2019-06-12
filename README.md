# Template - OpenGL - C++

## Status

|                                                                   LICENSE                                                                    |                                                                     Linux                                                                     |                                                                             Windows                                                                             |
| :------------------------------------------------------------------------------------------------------------------------------------------: | :-------------------------------------------------------------------------------------------------------------------------------------------: | :-------------------------------------------------------------------------------------------------------------------------------------------------------------: |
| [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://github.com/tobanteGaming/template-opengl/blob/master/LICENSE) | [![Build Status](https://travis-ci.org/tobanteGaming/template-opengl.svg?branch=master)](https://travis-ci.org/tobanteGaming/template-opengl) | [![AppVeyor Build status](https://img.shields.io/appveyor/ci/tobanteGaming/template-opengl.svg)](https://ci.appveyor.com/project/tobanteGaming/template-opengl) |

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
