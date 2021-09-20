#pragma once

#include "Entity.h"
#include "Core/Window.h"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "Renderer/VertexArray.h"

namespace PetrolEngine {
	struct Vertex {
		glm::vec3 position;
		glm::vec2 texCoords;
		glm::vec3 normal;
		glm::vec3 tangent;
		glm::vec3 bitangent;

		Vertex(
			glm::vec3 position  = glm::vec3(0.0f),
			glm::vec2 texCoords = glm::vec2(0.0f),
			glm::vec3 normal    = glm::vec3(0.0f),
			glm::vec3 tangent   = glm::vec3(0.0f),
			glm::vec3 bitangent = glm::vec3(0.0f) ):
			position ( position  ),
			texCoords( texCoords ),
			normal   ( normal    ),
			tangent  ( tangent   ),
			bitangent( bitangent ) {}
	};

	class Entity;

	class Tag {
	public:
		std::string  name;
		entt::entity parent;

		Tag(std::string _name = "", entt::entity _parent = entt::null);
	};

	class Transform {
	public:
		glm::vec3 position       = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 scale          = glm::vec3(1.0f, 1.0f, 1.0f);
		glm::quat rotation       = glm::quat(0.0f, 0.0f, 0.0f, 0.0f);
		glm::mat4 transformation = glm::mat4(1.0f);

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
		std::shared_ptr<VertexBuffer> vertexBuffer;
		std::shared_ptr< IndexBuffer>  indexBuffer;
		std::shared_ptr< VertexArray>  vertexArray;
		Material material;

		Mesh();
		Mesh(
			const std::vector<Vertex>& vertices,
			const std::vector< uint >& indices,
			Material     material,
			VertexLayout layout = {
				{"position" , ShaderDataType::Float3},
				{"texCords" , ShaderDataType::Float2},
				{"normal"   , ShaderDataType::Float3},
				{"tangent"  , ShaderDataType::Float3},
				{"bitangent", ShaderDataType::Float3}
			}
		);

		~Mesh() = default;
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
		void updateViewMatrix(const glm::vec3& position);
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

		void update(std::shared_ptr<Window> window);
	};
	class ExternalScript {
		virtual void onUpdate() = 0;
		virtual void onStart () = 0;
	};

}
