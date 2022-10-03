#pragma once

#define GLM_ENABLE_EXPERIMENTAL
//#define GLFW_INCLUDE_VULKAN
#define GLFW_INCLUDE_NONE

// Math
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/glm.hpp>

// Standard renderers
#include <glad/glad.h>
#include <vulkan/vulkan.h>

// Windowing libs
#include <GLFW/glfw3.h>

// STD
#include <filesystem>
#include <iostream>
#include <optional>
#include <vector>
#include <string>
#include <memory>
#include <thread>
#include <future>
#include <cmath>

// Assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// ECS library (Entity-Component System)
#include <entt/entt.hpp>

// Engine insides
#include "DebugTools.h"
#include "Aliases.h"
#include "Core/Logger.h"