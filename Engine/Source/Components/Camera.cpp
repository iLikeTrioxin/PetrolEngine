#include <PCH.h>

#include "Components/Camera.h"
#include "Components/Entity.h"
#include "Components/Transform.h"

namespace PetrolEngine {
    // Camera
    Camera::Camera() { updatePerspective(); }

    void Camera::updatePerspective() {
        perspective = glm::perspective(glm::radians(zoom), (float) resolution.x / (float) resolution.y, near, far);
    }

    void Camera::updateView() { LOG_FUNCTION();
        Transform t = transform->getRelativeTransform();

        this->view = glm::lookAt(
            t.position,
            t.position + t.forward,
            t.up
        );
    }
}