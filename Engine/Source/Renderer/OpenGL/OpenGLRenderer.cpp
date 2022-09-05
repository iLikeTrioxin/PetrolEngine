#include <PCH.h>

#include "OpenGLRenderer.h"
#include "Renderer/RendererInterface/TextureI.h"
#include "Renderer/Renderer/Texture.h"
#include "../../Core/Files.h"
#include "Components/Transform.h"
#include "Components/Mesh.h"
#include "Renderer/Renderer/Text.h"

// TODO: !!!!! REMOVE STATIC RENDERER DEPENDENCY !!!!!

#include "Renderer/Renderer/Shader.h"

namespace PetrolEngine {

	void OpenGLRenderer::getDeviceConstantValue(DeviceConstant deviceConstant, void* outputBuffer) {
		auto openGLDeviceConstant = openGLDeviceConstants.find(deviceConstant);

		glGetIntegerv(openGLDeviceConstant->second, (GLint*) outputBuffer);
	}


    void OpenGLRenderer::drawQuad2D(const Material& material, const Transform& transform) {
        const Vector<Vertex> quadVertices = {
                   // position           // texture coords
            Vertex({-1.0f, -1.0f, 0.0f}, {0.0f, 0.0f}),
            Vertex({ 1.0f,  1.0f, 0.0f}, {1.0f, 1.0f}),
            Vertex({-1.0f,  1.0f, 0.0f}, {0.0f, 1.0f}),

            Vertex({-1.0f, -1.0f, 0.0f}, {0.0f, 0.0f}),
            Vertex({ 1.0f, -1.0f, 0.0f}, {1.0f, 0.0f}),
            Vertex({ 1.0f,  1.0f, 0.0f}, {1.0f, 1.0f})
        };

        glUseProgram(material.shader->ID);





    }

	void OpenGLRenderer::setViewport(int x, int y, int width, int height) {
		glViewport(x, y, width, height);
	}

	int OpenGLRenderer::init(bool debug) {
        LOG("Initializing OpenGL.", 1);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            LOG("Initializing OpenGL failed.", 3);
			return 1;
		}

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		return 0;
	}

	void OpenGLRenderer::renderText(const String& text, const Transform& transform, const Material& material, const Camera* camera) { LOG_FUNCTION();
        /*
        String vertexShaderSource   = ReadFile("../Hei/Resources/Shaders/textShader.vert");
        String fragmentShaderSource = ReadFile("../Hei/Resources/Shaders/textShader.frag");

		auto shader = Shader::load(
			"textShader",
            vertexShaderSource.c_str(),
            fragmentShaderSource.c_str(),
            nullptr
		);
         */

		glUseProgram(material.shader->ID);

		static auto perv = glm::ortho(
            0, camera->resolution.x,
            0, camera->resolution.y
        );
		
		{ LOG_SCOPE("Setting shader values.");
			material.shader->setMat4("projection", perv);
			material.shader->setInt ("text"      , 0   );
		}

		glActiveTexture(GL_TEXTURE0);

		static Vector<Vertex> squareVertices({{}, {}, {}, {}, {}, {} });
		static Vector< uint > squareIndices ({ 0,  1,  2,  3,  4,  5 });

        squareVertices.reserve(text.length() * 6);
        squareIndices .reserve(text.length() * 6);

		static Mesh characterMesh = Mesh(squareVertices, squareIndices, Material());

		float x = transform.position.x;
		float y = transform.position.y;

        Text::FontAtlas atlas = Text::getAtlas("arial");
        auto a = material.textures[0];

        glBindTexture(GL_TEXTURE_2D, a->getID());

        // iterate through all characters
		for (auto c : text) {
			LOG_SCOPE("Rendering character");

            auto ch = atlas.characters[c];

			float xPos = x +              ch.bearing.x  * transform.scale.x;
			float yPos = y - (ch.size.y - ch.bearing.y) * transform.scale.y;

			float w = ch.size.x * transform.scale.x;
			float h = ch.size.y * transform.scale.y;

            for(int i = 0; i < 6; i++)
                squareIndices.push_back(squareVertices.size() + i);

            squareVertices.push_back(Vertex({xPos    , yPos + h, 0.f}, {ch.coords.x, ch.coords.y}));
            squareVertices.push_back(Vertex({xPos    , yPos    , 0.f}, {ch.coords.x, ch.coords.w}));
            squareVertices.push_back(Vertex({xPos + w, yPos    , 0.f}, {ch.coords.z, ch.coords.w}));
            squareVertices.push_back(Vertex({xPos    , yPos + h, 0.f}, {ch.coords.x, ch.coords.y}));
            squareVertices.push_back(Vertex({xPos + w, yPos    , 0.f}, {ch.coords.z, ch.coords.w}));
            squareVertices.push_back(Vertex({xPos + w, yPos + h, 0.f}, {ch.coords.z, ch.coords.y}));

			// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
			x += (float) (ch.advance >> 6) * transform.scale.x; // bitshift by 6 to get value in pixels (2^6 = 64)
		}

        characterMesh.vertexBuffer->setData(squareVertices.data(), squareVertices.size() * sizeof(Vertex));
        characterMesh. indexBuffer->setData(squareIndices .data(), squareIndices .size() * sizeof( uint ));

        glBindVertexArray(characterMesh.vertexArray->getID());
        //glBindVertexArray(0);
        //glBindBuffer(GL_ARRAY_BUFFER, characterMesh.vertexBuffer->getID());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, characterMesh.indexBuffer->getID());

        glDrawElements(GL_TRIANGLES, (int) characterMesh.indexBuffer->getSize(), GL_UNSIGNED_INT, nullptr);

        squareVertices.clear();
        squareIndices .clear();
	}

    void OpenGLRenderer::renderMesh(const Ref<VertexArrayI>& vao, const Transform& transform, const Material& material, const Camera* camera) { LOG_FUNCTION();
		auto shader = material.shader;

		glUseProgram(shader->ID);
		
        // Applying them to shader used by mesh
		shader->setMat4("model", transform.transformation);
		shader->setMat4("pav"  , camera->getPerspective() * camera->getViewMatrix());

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

		for (uint32 textureIndex = 0; textureIndex < material.textures.size(); textureIndex++) { LOG_SCOPE("Assigning texture");
			Ref<TextureI> texture = material.textures[textureIndex];

			glActiveTexture(GL_TEXTURE0  + textureIndex);
			glBindTexture  (GL_TEXTURE_2D, texture->getID());

            shader->setUint("texture_diffuse"  + toString( diffuseNumber), textureIndex);
			/*
			switch (texture->type) {
				case TextureI::TextureType::DIFFUSE : shader->setUint("texture_diffuse"  + toString( diffuseNumber), textureIndex); continue;
				case TextureI::TextureType::HEIGHT  : shader->setUint("texture_height"   + toString(  heightNumber), textureIndex); continue;
				case TextureI::TextureType::NORMAL  : shader->setUint("texture_normal"   + toString(  normalNumber), textureIndex); continue;
                case TextureI::TextureType::SPECULAR: shader->setUint("texture_specular" + toString(specularNumber), textureIndex); continue;
				
				default: continue;
			}*/
		}

		glBindVertexArray(vao->getID());
		
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.indexBuffer->getID());

		glDrawElements(GL_TRIANGLES, (int) vao->getIndexBuffer()->getSize(), GL_UNSIGNED_INT, nullptr);
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