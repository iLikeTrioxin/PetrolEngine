#include "PrecompiledHeader.h"
#include "Components.h"
#include "Game.h"
#include "Renderer.h"
#include "Window.h"

namespace Engine {

    // Tag
   Tag::Tag(std::string _name, entt::entity _parent) :
        name(_name), parent(_parent) {};

    // Transform
    void Transform::updateTransformMatrix() {
        glm::mat4& matrix = this->transformation;
        
        matrix  = glm::translate(matrix, this->position);
        matrix  = glm::scale(matrix, this->scale);
        matrix *= glm::toMat4(this->rotation);
        
    }

    // Mesh
         Mesh::Mesh(std::vector<Vertex> _vertices, std::vector<uint> _indices, Material _material) :
        vertices(_vertices), indices(_indices), material(_material) {
        initalizeBuffers();
        fillBufferWithData();
    }
	void Mesh::initalizeBuffers() {
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
	}
    void Mesh::fillBufferWithData() {
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

        glBufferData(GL_ARRAY_BUFFER        , sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof( uint ) * indices .size(), indices .data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

        /*
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, tangent));

        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, bitangent));
        */

        glBindVertexArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    uint Mesh::getVAO() {
        return VAO;
    }
    uint Mesh::getVBO() {
        return VBO;
    }
    uint Mesh::getEBO() {
        return EBO;
    }

    // Camera
         Camera::Camera(){
        updateCameraVectors();
    }
    void Camera::updatePerspectiveMatrix(float aspectRatio) {
        this->perspective = glm::perspective(glm::radians(Zoom), aspectRatio, near, far);
    }
    void Camera::updateViewMatrix(glm::vec3 position) {
        this->view = glm::lookAt(position, position + front, up);
    }
    void Camera::updateCameraVectors()
    {
        float x = cos(Pitch);

        front.x = cos( Yaw ) * x;
        front.y = sin(Pitch);
        front.z = sin( Yaw ) * x;

        front   = glm::normalize(front);
        right   = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
        up      = glm::normalize(glm::cross(right, front));
    }

    // Movement
         Movement::Movement(Transform* trans) :
        transform(trans) {};
    void Movement::update(){
        auto& camera = mainCamera.getComponent<Camera>();
        auto  window = Renderer::getWindow();

        if (glfwGetKey(window->windowHandle, GLFW_KEY_LEFT_SHIFT))
            currentSpeed = runSpeed;
        else
            currentSpeed = walkSpeed;

        if (glfwGetKey(window->windowHandle, GLFW_KEY_W))
            transform->position += camera.front * (float)deltaTime * currentSpeed;
        if (glfwGetKey(window->windowHandle, GLFW_KEY_S))
            transform->position -= camera.front * (float)deltaTime * currentSpeed;
        if (glfwGetKey(window->windowHandle, GLFW_KEY_A))
            transform->position -= camera.right * (float)deltaTime * currentSpeed;
        if (glfwGetKey(window->windowHandle, GLFW_KEY_D))
            transform->position += camera.right * (float)deltaTime * currentSpeed;

        camera.Yaw   += deltaXMousePos * 0.005;
        camera.Pitch -= deltaYMousePos * 0.005;
        
        if (camera.Pitch > 1.4f)
            camera.Pitch = 1.4f;
        if (camera.Pitch < -1.4f)
            camera.Pitch = -1.4f;

        camera.updateCameraVectors();
};
}