#include <PCH.h>

#include "OpenGLRenderer.h"
#include "../Texture.h"
#include "../../Core/Files.h"
#include "../Text.h"

namespace PetrolEngine {

	void OpenGLRenderer::getDeviceConstantValue(DeviceConstant deviceConstant, void* outputBuffer) {
		auto OpenGLdeviceConstant = OpenGLDeviceConstants.find(deviceConstant);

		glGetIntegerv(OpenGLdeviceConstant->second, (GLint*) outputBuffer);
	}

	void OpenGLRenderer::setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
		glViewport(x, y, width, height);
	}

	int OpenGLRenderer::init(bool debug) {
        DEBUG_LOG("[*] Initializing OpenGL.");

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            DEBUG_LOG("[!] Initializing OpenGL failed.");
			return 1;
		}

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		return 0;
	}

	void OpenGLRenderer::renderText(const std::string& text, Transform& transform) {
		LOG_FUNCTION();

		auto shader = Shader::load(
			"textShader",
			ReadFile("../Engine/Resources/Shaders/textShader.vert"),
			ReadFile("../Engine/Resources/Shaders/textShader.frag")
		);

		glUseProgram(shader->ID);

		static auto perv = glm::ortho(0.0f, 800.f, 0.0f, 500.f);
		
		{
			LOG_SCOPE("Setting shader values.");

			shader->setMat4("projection", perv);
			shader->setInt("text", 0);
		}

		glActiveTexture(GL_TEXTURE0);

		static std::vector<Vertex> squereVerts  ({ {}, {}, {}, {}, {}, {} });
		static std::vector< uint > squereIndices({ 0,  1,  2,  3,  4,  5  });
		static Mesh characterMesh = Mesh(squereVerts, squereIndices, Material());

		float x = transform.position.x;
		float y = transform.position.y;
		// iterate through all characters
		std::string::const_iterator c;
		for (c = text.begin(); c != text.end(); c++) {
			LOG_SCOPE("Rendering character");

			Text::Character ch = Text::get(*c);
			
			glBindTexture(GL_TEXTURE_2D, ch.texture->getID());
			
			float xpos = x + ch.Bearing.x * transform.scale.x;
			float ypos = y - (ch.Size.y - ch.Bearing.y) * transform.scale.y;

			float w = ch.Size.x * transform.scale.x;
			float h = ch.Size.y * transform.scale.y;

			// update VBO for each character
			
			squereVerts = {
				Vertex( glm::vec3(xpos    , ypos + h, 0.f), glm::vec2( 0.0f, 0.0f ) ),
				Vertex( glm::vec3(xpos    , ypos    , 0.f), glm::vec2( 0.0f, 1.0f ) ),
				Vertex( glm::vec3(xpos + w, ypos    , 0.f), glm::vec2( 1.0f, 1.0f ) ),
				Vertex( glm::vec3(xpos    , ypos + h, 0.f), glm::vec2( 0.0f, 0.0f ) ),
				Vertex( glm::vec3(xpos + w, ypos    , 0.f), glm::vec2( 1.0f, 1.0f ) ),
				Vertex( glm::vec3(xpos + w, ypos + h, 0.f), glm::vec2( 1.0f, 0.0f ) )
			};

			characterMesh.vertexBuffer->setData(squereVerts.data(), squereVerts.size() * sizeof(Vertex));
			
			glBindVertexArray(characterMesh.vertexArray->getID());

			//glBindBuffer(GL_ARRAY_BUFFER, a.vertexBuffer->getID());
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, characterMesh.indexBuffer->getID());
			
			glDrawElements(GL_TRIANGLES, characterMesh.indexBuffer->getSize(), GL_UNSIGNED_INT, nullptr);

			// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
			x += (ch.Advance >> 6) * transform.scale.x; // bitshift by 6 to get value in pixels (2^6 = 64)
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

		shader->setInt  ( "light[0].lightType", 1                        );
		shader->setVec3 ( "light[0].direction", -1.f, 0.f, 1.f           );
		shader->setVec3 ( "light[0].ambient"  ,  .2f, .2f, .2f           );
		shader->setVec3 ( "light[0].diffuse"  , glm::vec3(1.f, 1.f, 1.f) );
		shader->setVec3 ( "light[0].specular" , 0.f, 0.f, 0.f            );

		// if (currentShader != mesh.material.shader->ID) {
		// 	mesh.material.shader->use();
		// 	currentShader = mesh.material.shader->ID;
		// }

		// loading textures into the buffers
		uint diffuseNumber  = 1;
		uint heightNumber   = 1;
		uint normalNumber   = 1;
		uint specularNumber = 1;

		for (uint textureIndex = 0; textureIndex < mesh.material.textures.size(); textureIndex++) {
			LOG_SCOPE("Assigning texture");
			
			std::shared_ptr<Texture> texture = mesh.material.textures[textureIndex];

			glActiveTexture(GL_TEXTURE0  + textureIndex);
			glBindTexture  (GL_TEXTURE_2D, texture->getID());
			
			switch (texture->type)
			{
			case TextureType::DIFFUSE : shader->setInt("texture_diffuse"  +  diffuseNumber, textureIndex); continue;
			case TextureType::HEIGHT  : shader->setInt("texture_height"   +   heightNumber, textureIndex); continue;
			case TextureType::NORMAL  : shader->setInt("texture_normal"   +   normalNumber, textureIndex); continue;
			case TextureType::SPECULAR: shader->setInt("texture_specular" + specularNumber, textureIndex); continue;
			
			default: continue;
			}
		}

		glBindVertexArray(mesh.vertexArray->getID());
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.indexBuffer->getID());

		glDrawElements(GL_TRIANGLES, mesh.indexBuffer->getSize(), GL_UNSIGNED_INT, nullptr);
	}
	
	void OpenGLRenderer::clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRenderer::resetBuffers() {
		glActiveTexture(GL_TEXTURE0);
	}
}