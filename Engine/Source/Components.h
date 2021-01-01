#pragma once

#include "Entity.h"

namespace Engine {
	struct Vertex {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texCoords;
		glm::vec3 tangent;
		glm::vec3 bitangent;
	};

	class Entity;

	extern double deltaXMousePos;
	extern double deltaYMousePos;
	extern double cursorXPos;
	extern double cursorYPos;

	extern double deltaTime;

	class Tag {
	public:
		std::string  name;
		entt::entity parent;

		Tag(std::string _name = "", entt::entity _parent = entt::null);
	};

	class Transform {
	public:
		glm::mat4 transformation = glm::mat4(1.0f);
		glm::vec3 position       = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 scale          = glm::vec3(1.0f, 1.0f, 1.0f);
		glm::quat rotation       = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);

		Transform() = default;

		void updateTransformMatrix();

		Transform& operator+=(const Transform& other) {
			this->position += other.position;
			this->rotation *= other.rotation;
			this->scale    *= other.scale;

			return *this;
		}
		Transform& operator-=(const Transform& other) {
			this->position += other.position;
			this->scale    *= other.scale;
			this->rotation *= glm::inverse(other.rotation);

			return *this;
		}
	};

	class Mesh {
	public:
		std::vector< Vertex > vertices;
		std::vector<  uint  > indices;
		Material material;

		Mesh() = default;
		Mesh(
			std::vector< Vertex > _vertices,
			std::vector<  uint  > _indices,
			Material _material);

		uint getVAO();
		uint getVBO();
		uint getEBO();
		void initalizeBuffers();
		void fillBufferWithData();

	private:
		uint VAO;
		uint VBO;
		uint EBO;
	};

	class Camera {
	public:
		glm::vec3 front       = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 right       = glm::vec3(1.0f, 0.0f, 0.0f);
		glm::vec3 up          = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::mat4 perspective = glm::mat4(1.0f);
		glm::mat4 view        = glm::mat4(1.0f);

		float Zoom  =  45.0f;
		float Yaw   = -90.0f;
		float Pitch =   0.0f;
		float near  =   0.1f;
		float far   = 100.0f;

		Camera();
		Camera(glm::vec3 _position);
		
		void updatePerspectiveMatrix(float aspectRatio);
		void updateViewMatrix(glm::vec3 position);
		void updateCameraVectors();
	};

	class DirectionalLight {
	public:
		glm::vec3 direction;
		glm::vec3 color;
		float intensity = 1.0f;
	};

	class Movement {
	public:
		Transform* transform;
		float walkSpeed =  2.0f;
		float  runSpeed = 10.0f;

		Movement(Transform* trans);

		void update();
	private:
		float currentSpeed = 0.0f;
	};
	class ExternalScript {
		virtual void onUpdate() = 0;
		virtual void onStart () = 0;
	};

}
