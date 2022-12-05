#include <PCH.h>

#include "OpenGLRenderer.h"
#include "Renderer/RendererInterface/Texture.h"
#include "../../Core/Files.h"
#include "Components/Transform.h"
#include "Components/Mesh.h"
#include "Renderer/Renderer/Text.h"
#include "OpenGL.h"
#include <Components/VertexData.h>
// TODO: !!!!! REMOVE STATIC RENDERER DEPENDENCY !!!!!

namespace PetrolEngine {

	void OpenGLRenderer::getDeviceConstantValue(DeviceConstant deviceConstant, void* outputBuffer) {
		auto openGLDeviceConstant = openGLDeviceConstants.find(deviceConstant);

		glGetIntegerv(openGLDeviceConstant->second, (GLint*) outputBuffer);
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

            vertexArray = OpenGL.newVertexArray();

            auto* vbo = OpenGL.newVertexBuffer(layout);
            auto* ibo = OpenGL.newIndexBuffer();

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

    void OpenGLRenderer::drawQuad2D(const Texture* texture, const Transform* transform, Shader* shader, const Camera* camera, glm::vec4 texCoords) {
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

	void OpenGLRenderer::setViewport(int x, int y, int width, int height) {
		glViewport(x, y, width, height);
	}

	int OpenGLRenderer::init(bool debug) {
        LOG("Initializing OpenGL.", 1);

		//if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        //    LOG("Initializing OpenGL failed.", 3);
		//	return 1;
		//}

		glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		return 0;
	}

	void OpenGLRenderer::renderText(const String& text, const Transform& transform, const Texture* atlas, Text::FontAtlas* fa, Shader* shader, const Camera* camera) { LOG_FUNCTION();
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
    void OpenGLRenderer::renderMesh(const VertexArray* vao, const Transform& transform, const Vector<const Texture*>& textures, Shader* shader, const Camera* camera) { LOG_FUNCTION();
		glUseProgram(shader->getID());

        struct View {
            glm::mat4 model;
            glm::mat4 projection;
            glm::mat4 view;
        } view;

        if(!fir){
            fir = true;
            ubo = OpenGL.newUniformBuffer(sizeof(View), 0);
        }

        view.model      = transform.transformation;
        view.projection = camera->getPerspective();
        view.view       = camera->getViewMatrix ();

        ubo->setData(&view, sizeof(View), 0);

        shader->bindUniformBuffer("View", ubo);
        //auto ia = glGetUniformBlockIndex(a, "_12_14"); // glGetUniformBlockIndex(a, "_14");
        //LOG(toString(ia), 3);

        //glUniformBlockBinding(a, ubo->getID(), 1);
        //glUniformBlockBinding(a, ubo->getID(), ia); // glGetUniformBlockIndex
        // Applying them to shader used by mesh
		//shader->setMat4("model", transform.transformation);
		//shader->setMat4("pav"  , camera->getPerspective() * camera->getViewMatrix());

		shader->setInt  ( "material.diffuse"  , 0   );
		shader->setInt  ( "material.specular" , 0   );
		shader->setFloat( "material.shininess", 1.f );

		shader->setInt  ( "light[0].lightType",  1                 );
		shader->setVec3 ( "light[0].direction", -1.0f,  0.0f, 1.0f );
		shader->setVec3 ( "light[0].ambient"  ,  0.2f,  0.2f, 0.2f );
		shader->setVec3 ( "light[0].diffuse"  ,  1.0f,  1.0f, 1.0f );
		shader->setVec3 ( "light[0].specular" ,  0.0f,  0.0f, 0.0f );

		// if (currentShader != mesh.material.shader->ID) {
		// 	mesh.material.shader->use();
		// 	currentShader = mesh.material.shader->ID;
		// }

		// loading textures into the buffers
		uint32 diffuseNumber  = 1;
		uint32 heightNumber   = 1;
		uint32 normalNumber   = 1;
		uint32 specularNumber = 1;

		for (uint32 textureIndex = 0; textureIndex < textures.size(); textureIndex++) { LOG_SCOPE("Assigning texture");
			const Texture* texture = textures[textureIndex];

			//glActiveTexture(GL_TEXTURE0  + textureIndex);
            //glBindTexture  (GL_TEXTURE_2D, texture->getID());
            glBindTextureUnit(shader->metadata.textures[textureIndex], texture->getID());

            // shader->setUint("texture_diffuse"  + toString( diffuseNumber), textureIndex);
			/*
			switch (texture->type) {
				case TextureI::TextureType::DIFFUSE : shader->setUint("texture_diffuse"  + toString( diffuseNumber), textureIndex); continue;
				case TextureI::TextureType::HEIGHT  : shader->setUint("texture_height"   + toString(  heightNumber), textureIndex); continue;
				case TextureI::TextureType::NORMAL  : shader->setUint("texture_normal"   + toString(  normalNumber), textureIndex); continue;
                case TextureI::TextureType::SPECULAR: shader->setUint("texture_specular" + toString(specularNumber), textureIndex); continue;
				
				default: continue;
			}*/
		}

        if(vao->getIndexBuffer() == nullptr)
            LOG("Index buffer is null at draw.", 3);

        if(vao->getVertexBuffers().size() == 0)
            LOG("No vertex buffers at draw.", 3);

		glBindVertexArray(vao->getID());
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vao->getIndexBuffer()->getID());

        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vao->getIndexBuffer()->getID());
        //glBindBuffer(GL_ARRAY_BUFFER, vao->getVertexBuffers()[0]->getID());

		glDrawElements(GL_TRIANGLES, (int) vao->getIndexBuffer()->getSize(), GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
	}

	/* Pseudo fragment shader
	* 
	* struct quad {
	*     textureSampler texture;
	*         
	* }
	* 
	* 
	* 
	* 
	*
	* 
	*/

    //void OpenGLRenderer::drawQuad2D(Material material, Transform transform) {
//
	//}
	
	void OpenGLRenderer::clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRenderer::resetBuffers() {
		glActiveTexture(GL_TEXTURE0);
	}
}