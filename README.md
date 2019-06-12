# Template - OpenGL

Template project for OpenGL programming using C++, GLFW, GLEW, GLM, IMGUI & SPDLOG.

## Status

|                                                                   LICENSE                                                                    |                                                                     macOS                                                                     |                                                                             Windows                                                                             |
| :------------------------------------------------------------------------------------------------------------------------------------------: | :-------------------------------------------------------------------------------------------------------------------------------------------: | :-------------------------------------------------------------------------------------------------------------------------------------------------------------: |
| [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://github.com/tobanteGaming/template-opengl/blob/master/LICENSE) | [![Build Status](https://travis-ci.org/tobanteGaming/template-opengl.svg?branch=master)](https://travis-ci.org/tobanteGaming/template-opengl) | [![AppVeyor Build status](https://img.shields.io/appveyor/ci/tobanteGaming/template-opengl.svg)](https://ci.appveyor.com/project/tobanteGaming/template-opengl) |

## Build

### With Makefile

```sh
cd $PROJECT_ROOT
make                # Release build
make win64          # Release build (Windows 64bit)
make debug          # Debug build
```

### With CMake

```sh
cd $PROJECT_ROOT
cmake -Bbuild -DCMAKE_BUILD_TYPE=Release .
cmake --build build --config Release
```

### Makefile

```sh
make doc            # Build doxygen html
make stats          # Count source lines (using cloc)
make format         # Format code (using clang-format)
```
