#pragma once

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

namespace PetrolEngine{
    struct Vertex {
        glm::vec3 position;
        glm::vec2 texCoords;
        glm::vec3 normal;
        glm::vec3 tangent;
        glm::vec3 bitangent;

        Vertex(
            glm::vec3 position  = glm::vec3(0.0f),
            glm::vec2 texCoords = glm::vec2(0.0f),
            glm::vec3 normal    = glm::vec3(0.0f),
            glm::vec3 tangent   = glm::vec3(0.0f),
            glm::vec3 bitangent = glm::vec3(0.0f) ):
            position ( position  ),
            texCoords( texCoords ),
            normal   ( normal    ),
            tangent  ( tangent   ),
            bitangent( bitangent ) {}
    };
}