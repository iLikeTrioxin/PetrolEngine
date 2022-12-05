#include <PCH.h>

#include "Mesh.h"

#include "Components/Vertex.h"
#include <Renderer/Renderer/Renderer.h>

namespace PetrolEngine {
    Mesh::Mesh(VertexLayout additionalLayout) {
        this->material         = Material();
        this->additionalLayout = additionalLayout;

        LOG("ADDITONAL LAYOUT: mesh", 3);

        auto vertexBufferS = Renderer::newVertexBuffer(  standardLayout);
        auto vertexBufferE = Renderer::newVertexBuffer(additionalLayout);
        auto indexBuffer   = Renderer::newIndexBuffer ();

        this->vertexArray = Renderer::createVertexArray();

        this->vertexArray->addVertexBuffer(vertexBufferS);
        this->vertexArray->addVertexBuffer(vertexBufferE);
        this->vertexArray-> setIndexBuffer( indexBuffer );
    }

    Mesh::Mesh() {
//        recalculateMesh();
    }

    Mesh::Mesh(
            const Vector<glm::vec3>& vertices,
            const Vector<     uint>& indices ,
            Material                 material,
            VertexLayout             additionalData) {
        this->vertices = vertices;
        this->indices  = indices;
        this->material = material;

        recalculateMesh();
    }

    void Mesh::recalculateMesh(void* additionalData, int64 additionalDataSize) {
        this->vertexArray = Renderer::createVertexArray();

        auto vertexBufferS = Renderer::newVertexBuffer(standardLayout);
        auto indexBuffer   = Renderer::newIndexBuffer ();
/*
        if(!additionalLayout.getElements().empty() && additionalData != nullptr && additionalDataSize != 0){
            auto vertexBufferE = Renderer::newVertexBuffer(additionalLayout);

            vertexBufferE->setData(additionalData, (int64) indices.size() * (int64) sizeof(Vertex));

            this->vertexArray->addVertexBuffer(vertexBufferE);
        }*/

        uint64 vertexCount = 0;

        if(vertices          .size() > vertexCount) vertexCount = vertices          .size();
        if(normals           .size() > vertexCount) vertexCount = normals           .size();
        if(textureCoordinates.size() > vertexCount) vertexCount = textureCoordinates.size();

        VertexData vertexData;

        vertexData.changeLayout(standardLayout);
        vertexData.resize(vertexCount);

        for(int i = 0; i < vertices          .size(); i++) vertexData[i]["position"] = vertices[i];
        for(int i = 0; i < normals           .size(); i++) vertexData[i]["normal"  ] = normals [i];
        for(int i = 0; i < textureCoordinates.size(); i++) vertexData[i]["texCords"] = textureCoordinates[i];

        vertexBufferS->setData(vertexData.data, (int64) vertexCount    * (int64) vertexData.elementSize);
        indexBuffer  ->setData(indices.data() , (int64) indices.size() * (int64) sizeof(uint));

        this->vertexArray-> setIndexBuffer( indexBuffer );
        this->vertexArray->addVertexBuffer(vertexBufferS);
    }

    void Mesh::invertFaces() {
        for(int i = 0; i < indices.size(); i += 3)
            swap(indices[i], indices[i + 2]);
    }

    Mesh createCube(float size) {
        float d = size / 2.0f;
        return Mesh({
            // front
            {-d, -d, d},
            { d, -d, d},
            { d,  d, d},
            {-d,  d, d},
            // back
            {-d, -d, -d},
            { d, -d, -d},
            { d,  d, -d},
            {-d,  d, -d}
        }, {
                0, 1, 2, 2, 3, 0, // front
                1, 5, 6, 6, 2, 1, // right
                7, 6, 5, 5, 4, 7, // back
                4, 0, 3, 3, 7, 4, // left
                4, 5, 1, 1, 0, 4, // bottom
                3, 2, 6, 6, 7, 3  // top
        });
    }
}