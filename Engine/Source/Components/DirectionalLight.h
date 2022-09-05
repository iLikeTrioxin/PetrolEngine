#pragma once

#include "Components/Component.h"

namespace PetrolEngine {
    class DirectionalLight: public Component {
    public:
        glm::vec3 direction;
        glm::vec3 color;
        float intensity = 1.0f;
    };
}