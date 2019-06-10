#pragma once

#include <array>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"

#include "core/settings.hpp"
#include "core/shader_source.hpp"
#include "core/warning.hpp"

namespace tobanteGaming
{
// Array
template<class T, size_t N>
using Array = std::array<T, N>;

// Function
template<class T>
using Function = std::function<T>;

// Map
template<class Key, class Value>
using Map = std::map<Key, Value>;

// String
using String = std::string;

// Pair
template<class T1, class T2>
using Pair = std::pair<T1, T2>;

// Pointer
template<class T>
using Pointer = std::unique_ptr<T>;

}  // namespace tobanteGaming