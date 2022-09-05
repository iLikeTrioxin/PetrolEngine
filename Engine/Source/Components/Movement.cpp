#include <PCH.h>

#include "Movement.h"
#include "Camera.h"
#include "Core/Window/Window.h"

namespace PetrolEngine {
    // Movement
    Movement::Movement(Camera* camera) :
            camera (camera) {};

    void Movement::onUpdate() { LOG_FUNCTION();
        float distance = (Window::isPressed(GLFW_KEY_LEFT_SHIFT) ? runSpeed : walkSpeed) * (float)deltaTime;

        if (Window::isPressed(GLFW_KEY_W)) transform->position += camera->transform->forward * distance;
        if (Window::isPressed(GLFW_KEY_S)) transform->position -= camera->transform->forward * distance;
        if (Window::isPressed(GLFW_KEY_A)) transform->position -= camera->transform->right   * distance;
        if (Window::isPressed(GLFW_KEY_D)) transform->position += camera->transform->right   * distance;

                transform->rotateY((float) -(deltaXMousePos * 0.005));
        camera->transform->rotateX((float) -(deltaYMousePos * 0.005));

        glm::vec3 angles = eulerAngles(camera->transform->rotation);

        if (angles.x >  1.5f) camera->transform->setRotationX( 1.5f);
        if (angles.x < -1.5f) camera->transform->setRotationX(-1.5f);
    }
}