#pragma once

#include <Aliases.h>

#include <glm/vec3.hpp>
#include <glm/matrix.hpp>

#include "Components/Component.h"

// TODO: make camera rotation work

namespace PetrolEngine {
    class Camera: public Component {
    public:
        glm::ivec2 resolution = glm::ivec2(1280, 720);

        float zoom  =  45.0f;
        float near  =   0.1f;
        float far   = 100.0f;

        Camera();

        void updatePerspective();
        void updateView();

        NO_DISCARD const glm::mat4& getViewMatrix () const { return view       ; };
        NO_DISCARD const glm::mat4& getPerspective() const { return perspective; };
    private:
        glm::mat4 perspective = glm::mat4(1.0f);
        glm::mat4 view        = glm::mat4(1.0f);
    };
}