#pragma once

#include "Components/Transform.h"
#include "Components/Entity.h"
#include "Components/Component.h"
#include "Components/Camera.h"

namespace PetrolEngine {
    class Movement: public Component {
    public:
        const float walkSpeed =  2.0f;
        const float  runSpeed = 10.0f;

        Movement(Camera* camera);

        Movement& operator=(const Movement&) { return *this; }


        void onStart() override {};
        void onUpdate() override;
    private:
        Camera* camera;
    };
}