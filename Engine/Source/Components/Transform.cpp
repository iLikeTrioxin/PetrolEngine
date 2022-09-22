#include <PCH.h>

#include "Transform.h"

namespace PetrolEngine{
    // Transform
    void Transform::updateTransformMatrix() {
        glm::mat4& matrix = this->transformation;

        matrix  = glm::translate(matrix, this->position);
        matrix  = glm::scale    (matrix, this->scale   );
        matrix *= glm::toMat4   (        this->rotation);
    }

    void Transform::setPosition(glm::vec3 position) {
        this->position = position;
        this->updateTransformMatrix();
    }

    void Transform::updateOrientation(){
        glm::quat r = rotation;

        for(Transform* p = parent; p; p = p->parent)
            r = p->rotation * r;

        forward = glm::rotate(r, glm::vec3(0.0f, 0.0f, -1.0f));
        right   = glm::rotate(r, glm::vec3(1.0f, 0.0f,  0.0f));
        up      = glm::rotate(r, glm::vec3(0.0f, 1.0f,  0.0f));
    }

    void Transform::setRotationX(float x, bool l) { rotateX(-(glm::eulerAngles(rotation).x - x), l); }
    void Transform::setRotationY(float y, bool l) { rotateY(-(glm::eulerAngles(rotation).y - y), l); }
    void Transform::setRotationZ(float z, bool l) { rotateZ(-(glm::eulerAngles(rotation).z - z), l); }

    void Transform::rotateX(float x, bool l) { rotate({ x, 0, 0 }, l); }
    void Transform::rotateY(float y, bool l) { rotate({ 0, y, 0 }, l); }
    void Transform::rotateZ(float z, bool l) { rotate({ 0, 0, z }, l); }

    void Transform::setRotation(glm::vec3 b, bool l) {
        rotate(-(glm::eulerAngles(rotation) - b), l);
    }

    void Transform::rotate(glm::vec3 angles, bool local) {
        auto angle = glm::quat(angles);

        rotation = local ? rotation * angle : angle * rotation;
        rotation = glm::normalize(rotation);

        updateOrientation();
        updateTransformMatrix();
    }
}