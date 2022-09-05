#pragma once

// ! This class can be used only using StaticRenderer context.

#include <Aliases.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/quaternion.hpp>

#include "Entity.h"
#include "Core/WindowInterface/WindowI.h"

#include "Renderer/RendererInterface/VertexArrayI.h"

#include "Components/Component.h"

#include "Transform.h"
#include "Vertex.h"
#include "Material.h"

namespace PetrolEngine {
    class Mesh: public Component {
	public:
		Ref<VertexBufferI> vertexBuffer;
		Ref< IndexBufferI>  indexBuffer;
		Ref< VertexArrayI>  vertexArray;
		Material material;

		Mesh();
		Mesh(
			const Vector<Vertex>& vertices,
			const Vector< uint >& indices,
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
}