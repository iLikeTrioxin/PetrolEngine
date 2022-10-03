#pragma once

#include "Core/Window/Window.h"

#include "Components/Component.h"
#include "Components/Transform.h"

namespace PetrolEngine {
    class TestRotationScript : public Component {
    public:
        void onUpdate() override {
            transform->rotateY( (float) deltaTime );
        }
    };
}