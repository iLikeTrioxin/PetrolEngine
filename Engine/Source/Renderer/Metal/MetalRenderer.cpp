#include <PCH.h>

#include "MetalRenderer.h"
#include "Renderer/RendererInterface/Texture.h"
#include "../../Core/Files.h"
#include "Components/Transform.h"
#include "Components/Mesh.h"
#include "Renderer/Renderer/Text.h"
#include "Metal.h"
#include <Components/VertexData.h>
// TODO: !!!!! REMOVE STATIC RENDERER DEPENDENCY !!!!!

namespace PetrolEngine {

	void MetalRenderer::getDeviceConstantValue(DeviceConstant deviceConstant, void* outputBuffer) {
		auto MetalDeviceConstant = MetalDeviceConstants.find(deviceConstant);
	}

    class Batch2D{
    public:
        Shader* shader;
        VertexArray* vertexArray;
        VertexData vertexData;

        VertexLayout layout = {{
            {"position", ShaderDataType::Float3},
            {"texCords", ShaderDataType::Float2},
            {"textureIndex", ShaderDataType::Int}
        }};

        Vector<const Texture*> textures;
        Vector<glm::vec3> vertices;
        Vector<glm::vec2> texCoords;
        Vector<uint> textureIndexes;
        Vector<uint> indices;

        struct Quad {
            const Texture* texture;

            glm::vec3 position;
            glm::vec2 size;

            glm::vec4 texCoords;
        };

        void addQuad(const Quad& quad){
            auto& pos = quad.position;

            this->vertices.emplace_back(pos.x + 0          , pos.y + 0          , 0);
            this->vertices.emplace_back(pos.x + quad.size.x, pos.y + 0          , 0);
            this->vertices.emplace_back(pos.x + quad.size.x, pos.y + quad.size.y, 0);
            this->vertices.emplace_back(pos.x + 0          , pos.y + quad.size.y, 0);

            const uint quadIndices[] = {0, 1, 2, 0, 2, 3};

            for(auto i : quadIndices)
                this->indices.emplace_back(i + this->vertices.size() - 4);

            this->texCoords.emplace_back(quad.texCoords.x, quad.texCoords.y);
            this->texCoords.emplace_back(quad.texCoords.z, quad.texCoords.y);
            this->texCoords.emplace_back(quad.texCoords.z, quad.texCoords.w);
            this->texCoords.emplace_back(quad.texCoords.x, quad.texCoords.w);

            //this->texCoords.push_back(quad.texCoords0);
            //this->texCoords.push_back(quad.texCoords1);
            int found = -1;
            for (int i = 0; i < this->textures.size(); i++){
                if (this->textures[i] == quad.texture){
                    found = i;
                    break;
                }
            }

            if (found == -1) {
                this->textures.push_back(quad.texture);
                found = this->textures.size() - 1;
            }

            for(int i = 0; i < 4; i++)
                this->textureIndexes.push_back(found);
        }


        VertexArray* prepare(){
            vertexData.resize(vertices.size());

            for(int i = 0; i < vertices.size(); i++){
                vertexData[i]["position"] = vertices[i];
                vertexData[i]["texCords"] = texCoords[i];
                vertexData[i]["textureIndex"] = textureIndexes[i];
            }

//            auto a1 = vertexArray->getVertexBuffers()[0];
//            auto a2 = vertexArray->getIndexBuffer  ()   ;

            vertexArray->getVertexBuffers()[0]->setData(vertexData.data , vertices.size() * vertexData.elementSize);
            vertexArray->getIndexBuffer  ()   ->setData(indices   .data(), indices.size() * sizeof(uint));

            return vertexArray;
        }

        void clear(){
            vertices.clear();
            texCoords.clear();
            textureIndexes.clear();
            indices.clear();
            textures.clear();
        }


        Batch2D(Shader* shader){
            this->shader = shader;

            vertexArray = Metal.newVertexArray();

            auto* vbo = Metal.newVertexBuffer(layout);
            auto* ibo = Metal.newIndexBuffer();

            vertexArray->addVertexBuffer(vbo);
            vertexArray-> setIndexBuffer(ibo);

            vertexData.changeLayout(layout);
        }
    };

    class Batcher2D{
    public:
        UnorderedMap<const Shader*, Batch2D> batches;

        void addQuad(const Batch2D::Quad& quad, Shader* shader, const Camera* camera){
            auto batch = this->batches.find(shader);

            if(batch == this->batches.end()){
                this->batches.emplace(shader, Batch2D(shader));
                batch = this->batches.find(shader);
            }

            batch->second.addQuad(quad);
        }

        struct BatchData{
            VertexArray* vertexArray;
            Shader* shader;
            Vector<const Texture*>* textures;

            BatchData(VertexArray* vertexArray, Shader* shader, Vector<const Texture*>* textures){
                this->vertexArray = vertexArray;
                this->shader = shader;
                this->textures = textures;
            }
        };

        Vector<BatchData> prepare(){
            Vector<BatchData> result;

            for(auto& batch : this->batches)
                result.emplace_back(batch.second.prepare(), batch.second.shader, &batch.second.textures);

            return result;
        }

        void clear(){
            for(auto& batch : this->batches) batch.second.clear();
        }

        Batcher2D(){

        }

    } batcher2D;

    void MetalRenderer::drawQuad2D(const Texture* texture, const Transform* transform, Shader* shader, const Camera* camera, glm::vec4 texCoords) {
        auto pos = transform->position;
        auto size = transform->scale;

        Batch2D::Quad quad = {
            texture,
            pos,
            size,
            texCoords
        };

        batcher2D.addQuad(quad, shader, camera);
    }

	void MetalRenderer::setViewport(int x, int y, int width, int height) {
		glViewport(x, y, width, height);
	}

	int MetalRenderer::init(bool debug) {
        LOG("Initializing Metal.", 1);

		//if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        //    LOG("Initializing Metal failed.", 3);
		//	return 1;
		//}

		glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		return 0;
	}

	void MetalRenderer::renderText(const String& text, const Transform& transform, const Texture* atlas, Text::FontAtlas* fa, Shader* shader, const Camera* camera) { LOG_FUNCTION();
//		glUseProgram(shader->getID());

//		static auto perv = glm::ortho(
//            0, camera->resolution.x,
//            0, camera->resolution.y
//        );

        float x = transform.position.x;
		float y = transform.position.y;

        //glBindTexture(GL_TEXTURE_2D, atlas->getID());

        // iterate through all characters
		for (auto c : text) {
			LOG_SCOPE("Rendering character");

            auto ch = fa->characters[c];

			float xPos = x +              ch.bearing.x  * transform.scale.x;
			float yPos = y - (ch.size.y - ch.bearing.y) * transform.scale.y;

			float w = ch.size.x * transform.scale.x;
			float h = ch.size.y * transform.scale.y;

            Batch2D::Quad quad{
                atlas,
                {xPos, yPos, 0},
                {w, h},
                ch.coords
            };

            batcher2D.addQuad(quad, shader, camera);
//            characterMesh.vertices.push_back({xPos    , yPos + h, 0.f});
//            characterMesh.vertices.push_back({xPos    , yPos    , 0.f});
//            characterMesh.vertices.push_back({xPos + w, yPos    , 0.f});
//            characterMesh.vertices.push_back({xPos    , yPos + h, 0.f});
//            characterMesh.vertices.push_back({xPos + w, yPos    , 0.f});
//            characterMesh.vertices.push_back({xPos + w, yPos + h, 0.f});
//
//            characterMesh.textureCoordinates.push_back({ch.coords.x, ch.coords.y});
//            characterMesh.textureCoordinates.push_back({ch.coords.x, ch.coords.w});
//            characterMesh.textureCoordinates.push_back({ch.coords.z, ch.coords.w});
//            characterMesh.textureCoordinates.push_back({ch.coords.x, ch.coords.y});
//            characterMesh.textureCoordinates.push_back({ch.coords.z, ch.coords.w});
//            characterMesh.textureCoordinates.push_back({ch.coords.z, ch.coords.y});

			// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
			x += (float) (ch.advance >> 6) * transform.scale.x; // bitshift by 6 to get value in pixels (2^6 = 64)
		}

        for(auto batch : batcher2D.prepare()){
            renderMesh(batch.vertexArray, Transform(), *batch.textures, batch.shader, camera);
            batcher2D.clear();
        }


//        characterMesh.recalculateMesh();
//
//        // characterMesh.vertexArray->getVertexBuffers()[0]->setData(squareVertices.data(), squareVertices.size() * sizeof(Vertex));
//        // characterMesh.vertexArray->getIndexBuffer  ()   ->setData(squareIndices .data(), squareIndices .size() * sizeof( uint ));
//
//        glBindVertexArray(characterMesh.vertexArray->getID());
//        //glBindVertexArray(0);
//        //glBindBuffer(GL_ARRAY_BUFFER, characterMesh.vertexBuffer->getID());
//        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, characterMesh.vertexArray->getIndexBuffer()->getID());
//
//        glDrawElements(GL_TRIANGLES, (int) characterMesh.vertexArray->getIndexBuffer()->getSize(), GL_UNSIGNED_INT, nullptr);
//
//        glBindVertexArray(0);
//
//        characterMesh.vertices.clear();
//        characterMesh.indices .clear();
//        characterMesh.textureCoordinates.clear();
	}

    bool fir = false;
    UniformBuffer* ubo = nullptr;
    void MetalRenderer::renderMesh(const VertexArray* vao, const Transform& transform, const Vector<const Texture*>& textures, Shader* shader, const Camera* camera) { LOG_FUNCTION();
	}
	
	void MetalRenderer::clear() {
	}

	void MetalRenderer::resetBuffers() {
	}
}