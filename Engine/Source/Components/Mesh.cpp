#include <PCH.h>

#include "Mesh.h"

#include "Components/Vertex.h"

#include "Renderer/Renderer/VertexArray.h"
#include "Renderer/Renderer/VertexBuffer.h"
#include "Renderer/Renderer/IndexBuffer.h"

namespace PetrolEngine {
    // Mesh
    Mesh::Mesh() {
        this->material     = Material();

        this->vertexBuffer = VertexBuffer::create({
            { "position" , ShaderDataType::Float3 },
            { "texCords" , ShaderDataType::Float2 },
            { "normal"   , ShaderDataType::Float3 },
            { "tangent"  , ShaderDataType::Float3 },
            { "bitangent", ShaderDataType::Float3 }
        });

        this->indexBuffer = IndexBuffer::create();
        this->vertexArray = VertexArray::create();

        this->vertexArray->addVertexBuffer(vertexBuffer);
        this->vertexArray-> setIndexBuffer( indexBuffer);
    }
    Mesh::Mesh(
            const Vector<Vertex>& vertices,
            const Vector< uint >& indices ,
            Material material             ,
            VertexLayout layout            ) {
        this->material = material;

        this->vertexBuffer = VertexBuffer::create(layout, (void*) vertices.data(), (int64)vertices.size() * (int64) sizeof(Vertex) );
        this-> indexBuffer =  IndexBuffer::create((void*)  indices.data(), (int64) indices.size() * (int64) sizeof( uint ) );

        this->vertexArray = VertexArray::create();

        this->vertexArray->addVertexBuffer(vertexBuffer);
        this->vertexArray->setIndexBuffer(indexBuffer);
    }
}