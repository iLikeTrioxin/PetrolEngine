#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/quaternion.hpp>

#include "Components/Component.h"

namespace PetrolEngine {
    // This class is pretty memory inefficient, but having
    // things like orientation alongside position and rotation
    // is just more convenient.
    class Transform: public InternalComponent {
    public:
        Transform* parent = nullptr;

        glm::vec3 position       = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 scale          = glm::vec3(1.0f, 1.0f, 1.0f);
        glm::quat rotation       = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);

        glm::vec3 forward = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 right   = glm::vec3(1.0f, 0.0f,  0.0f);
        glm::vec3 up      = glm::vec3(0.0f, 1.0f,  0.0f);

        glm::mat4 transformation = glm::mat4(1.0f);

        void setPosition(glm::vec3 position);

        void setRotationX(float x, bool local = true);
        void setRotationY(float y, bool local = true);
        void setRotationZ(float z, bool local = true);

        void rotateX(float x, bool local = true);
        void rotateY(float y, bool local = true);
        void rotateZ(float z, bool local = true);

        void setRotation(glm::vec3 angles, bool local = true);
        void    rotate  (glm::vec3 angles, bool local = true);

        //Transform() = default;
        Transform(
            glm::vec3 position       = glm::vec3(0.f)         ,
            glm::vec3 scale          = glm::vec3(1.f)         ,
            glm::quat rotation       = glm::quat(1.f, 0, 0, 0),
            glm::mat4 transformation = glm::mat4(1.f)           ):
                      position	    (position      ),
                      scale		    (scale         ),
                      rotation	    (rotation      ),
                      transformation(transformation) {}

        void updateTransformMatrix();
        void updateOrientation();

        Transform getRelativeTransform(){
            Transform result = Transform();

            for(Transform* t = this; t != nullptr; t = t->parent)
                result += *t;

            return result;
        }

        Transform& operator+=(const Transform& other) {
            this->position += other.position;
            this->rotation  = other.rotation * this->rotation;
            this->scale    *= other.scale;

            updateOrientation();
            updateTransformMatrix();

            return *this;
        }

        Transform& operator-=(const Transform& other) {
            this->position += other.position;
            this->scale    *= other.scale;
            this->rotation *= glm::inverse(other.rotation);

            updateOrientation();
            updateTransformMatrix();

            return *this;
        }
    };
}