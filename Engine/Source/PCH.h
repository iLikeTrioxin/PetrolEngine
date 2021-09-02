#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#define GLFW_INCLUDE_VULKAN

// OpenGL
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// STD
#include <filesystem>
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <thread>

// Assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// Other
#include <entt/entt.hpp>
#include <future>
#include "DebugTools.h"
#include "Renderer/Material.h"
#include "Aliases.h"

#ifndef NDEBUG
#define debug_log(x) std::cout<<x<<std::endl
#else
#define debug_log(x)
#endif

#define log_and_return(x, y) { debug_log(x); return y; }
