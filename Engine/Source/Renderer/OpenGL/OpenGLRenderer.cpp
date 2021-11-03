#include <PCH.h>

#include "OpenGLRenderer.h"
#include "../Texture.h"
#include "../../Core/Files.h"
#include "../Text.h"

namespace PetrolEngine {

	void OpenGLRenderer::getDeviceConstantValue(DeviceConstant deviceConstant, void* outputBuffer) {
		auto openGLDeviceConstant = openGLDeviceConstants.find(deviceConstant);

		glGetIntegerv(openGLDeviceConstant->second, (GLint*) outputBuffer);
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

		glEnable(GL_DEPTH_TEST); //-V525
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		return 0;
	}

	void OpenGLRenderer::renderText(const std::string& text, Transform& transform) {
		LOG_FUNCTION();

		auto shader = Shader::load(
			"textShader",
			ReadFile("../Hei/Resources/Shaders/textShader.vert"),
			ReadFile("../Hei/Resources/Shaders/textShader.frag")
		);

		glUseProgram(shader->ID);

		static auto perv = glm::ortho(0.0f, 800.f, 0.0f, 500.f);
		
		{
			LOG_SCOPE("Setting shader values.");

			shader->setMat4("projection", perv);
			shader->setInt("text", 0);
		}

		glActiveTexture(GL_TEXTURE0);

		static std::vector<Vertex> squareVertices({{}, {}, {}, {}, {}, {} });
		static std::vector< uint > squareIndices ({ 0,  1,  2,  3,  4,  5  });
		static Mesh characterMesh = Mesh(squareVertices, squareIndices, Material());

		float x = transform.position.x;
		float y = transform.position.y;

		// iterate through all characters
		std::string::const_iterator c;
		for (c = text.begin(); c != text.end(); ++c) {
			LOG_SCOPE("Rendering character");

			Text::Character ch = Text::get(*c);
			
			glBindTexture(GL_TEXTURE_2D, ch.texture->getID());
			
			float xPos = x + (float) ch.Bearing.x * transform.scale.x;
			float yPos = y - (float) (ch.Size.y - ch.Bearing.y) * transform.scale.y;

			float w = (float) ch.Size.x * transform.scale.x;
			float h = (float) ch.Size.y * transform.scale.y;

			// update VBO for each character

            // + 0 are used here to align arguments in clion editor
            // it will be stripped by compiler anyway
            squareVertices = {
				Vertex({xPos + 0, yPos + h, 0.f}, {0.0f, 0.0f } ),
				Vertex({xPos + 0, yPos + 0, 0.f}, {0.0f, 1.0f } ),
				Vertex({xPos + w, yPos + 0, 0.f}, {1.0f, 1.0f } ),
				Vertex({xPos + 0, yPos + h, 0.f}, {0.0f, 0.0f } ),
				Vertex({xPos + w, yPos + 0, 0.f}, {1.0f, 1.0f } ),
				Vertex({xPos + w, yPos + h, 0.f}, {1.0f, 0.0f } )
			};

			characterMesh.vertexBuffer->setData(squareVertices.data(), squareVertices.size() * sizeof(Vertex));
			
			glBindVertexArray(characterMesh.vertexArray->getID());

			//glBindBuffer(GL_ARRAY_BUFFER, a.vertexBuffer->getID());
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, characterMesh.indexBuffer->getID());
			
			glDrawElements(GL_TRIANGLES, (int) characterMesh.indexBuffer->getSize(), GL_UNSIGNED_INT, nullptr);

			// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
			x += (float) (ch.Advance >> 6) * transform.scale.x; // bitshift by 6 to get value in pixels (2^6 = 64)
		}
	}

	void OpenGLRenderer::renderMesh(Mesh& mesh, Transform& transform, Camera& camera) {
		LOG_FUNCTION();

		auto shader = mesh.material.shader;

		glUseProgram(shader->ID);
		
        // Applying them to shader used by mesh
		shader->setMat4("model", transform.transformation);
		shader->setMat4("pav"  , camera.perspective * camera.view);
		
		shader->setInt  ( "material.diffuse"  , 0   );
		shader->setInt  ( "material.specular" , 0   );
		shader->setFloat( "material.shininess", 1.f );

		shader->setInt  ( "light[0].lightType", 1                     );
		shader->setVec3 ( "light[0].direction", -1.f,  0.f, 1.f );
		shader->setVec3 ( "light[0].ambient"  ,  .2f,  .2f, .2f );
		shader->setVec3 ( "light[0].diffuse"  ,  1.f,  1.f, 1.f );
		shader->setVec3 ( "light[0].specular" ,  0.f,  0.f, 0.f );

		// if (currentShader != mesh.material.shader->ID) {
		// 	mesh.material.shader->use();
		// 	currentShader = mesh.material.shader->ID;
		// }

		// loading textures into the buffers
		uint diffuseNumber  = 1;
		uint heightNumber   = 1;
		uint normalNumber   = 1;
		uint specularNumber = 1;

		for (uint textureIndex=0; textureIndex < mesh.material.textures.size(); textureIndex++) { LOG_SCOPE("Assigning texture");
			Ref<Texture> texture = mesh.material.textures[textureIndex];

			glActiveTexture(GL_TEXTURE0  + textureIndex);
			glBindTexture  (GL_TEXTURE_2D, texture->getID());
			
			switch (texture->type)
			{
			case TextureType::DIFFUSE : shader->setUint("texture_diffuse"  +  diffuseNumber, textureIndex); continue;
			case TextureType::HEIGHT  : shader->setUint("texture_height"   +   heightNumber, textureIndex); continue;
			case TextureType::NORMAL  : shader->setUint("texture_normal"   +   normalNumber, textureIndex); continue;
			case TextureType::SPECULAR: shader->setUint("texture_specular" + specularNumber, textureIndex); continue;
			
			default: continue;
			}
		}

		glBindVertexArray(mesh.vertexArray->getID());
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.indexBuffer->getID());

		glDrawElements(GL_TRIANGLES, (int) mesh.indexBuffer->getSize(), GL_UNSIGNED_INT, nullptr);
	}
	
	void OpenGLRenderer::clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRenderer::resetBuffers() {
		glActiveTexture(GL_TEXTURE0);
	}
}