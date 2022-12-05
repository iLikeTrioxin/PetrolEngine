#pragma once

// ! This class can be used only using StaticRenderer context.

// TODO: raw pointers
#include <Aliases.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/quaternion.hpp>

#include "Entity.h"
#include "Core/WindowInterface/WindowI.h"

#include "Renderer/RendererInterface/VertexArray.h"

#include "Components/Component.h"

#include "Transform.h"
#include "Vertex.h"
#include "Material.h"

#include "VertexData.h"

/*
 * TODO:
 *  - switch to raw pointers
 *  - add physix
 *  - add networking
 *  - add lighting
 *
 *  - repair vulkan
 *  - add animation
 */

namespace PetrolEngine {

    const VertexLayout standardLayout = VertexLayout({
        {"position" , ShaderDataType::Float3},
        {"texCords" , ShaderDataType::Float2},
        {"normal"   , ShaderDataType::Float3}
    });

    class Mesh: public Component {
    public:
        VertexLayout additionalLayout;

    public:
        Material material;

        Vector<     uint> indices;
        Vector<glm::vec3> vertices;
        Vector<glm::vec3> normals;
        Vector<glm::vec2> textureCoordinates;

        Ref<VertexArray> vertexArray;
    public:
        Mesh(VertexLayout additionalLayout);
        Mesh();

        void invertFaces();
        void recalculateMesh(void* additionalData=nullptr, int64 additionalDataSize=0);

        NO_DISCARD
        Ref<VertexArray> getVertexArray() const { return vertexArray; }

		Mesh(
			const Vector<glm::vec3>& vertices,
			const Vector<     uint>& indices,
			Material                 material = {},
			VertexLayout             layout = VertexLayout({
				{"position" , ShaderDataType::Float3},
				{"texCords" , ShaderDataType::Float2},
				{"normal"   , ShaderDataType::Float3},
				{"tangent"  , ShaderDataType::Float3},
				{"bitangent", ShaderDataType::Float3}
            })
		);

		~Mesh() = default;
	};

    Mesh createCube(float size = 2.0f);
}