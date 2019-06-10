#pragma once

// STL
#include <array>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

// OPENGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

// IMGUI
#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"

// CORE
#include "core/log.hpp"
#include "core/settings.hpp"
#include "core/shader_source.hpp"
#include "core/warning.hpp"

namespace tobanteGaming
{
// Array
template<class Type, size_t Size>
using Array = std::array<Type, Size>;

// Function
template<class Type>
using Function = std::function<Type>;

// Map
template<class Key, class Value>
using Map = std::map<Key, Value>;

// String
using String = std::string;

// Pair
template<class FirstType, class SecondType>
using Pair = std::pair<FirstType, SecondType>;

// Pointer
template<class Type>
using Pointer = std::unique_ptr<Type>;

}  // namespace tobanteGaming