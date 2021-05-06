#pragma once

#define GLM_ENABLE_EXPERIMENTAL

// OpenGL
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// STD
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
#include <EnTT/single_include/entt/entt.hpp>
#include <future>
#include "Material.h"

template<typename T>
using Ptr = std::unique_ptr<T>;

#define uint unsigned int

#ifdef _DEBUG
#define debug_log(x) std::cout<<x<<std::endl
#else
#define debug_log(x)
#endif
