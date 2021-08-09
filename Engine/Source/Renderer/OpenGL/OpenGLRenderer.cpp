#include "../../PCH.h"

#include "OpenGLRenderer.h"
#include "../Texture.h"
#include "../../Core/Files.h"
#include "../Text.h"

namespace Engine {
	//Renderer::~Renderer() {
	//	for (unsigned int i = 0; i < loadedShaders.size(); i++) {
	//		glDeleteProgram(loadedShaders[i].ID);
	//	}
	//}
	//Shader& Renderer::loadShader(const char* vertexPath, const char* fragmentPath, const char* geometryPath) {
	//	return get().internalLoadShader(vertexPath, fragmentPath, geometryPath);
	//}
	//Shader& Renderer::internalLoadShader(const char* vertexPath, const char* fragmentPath, const char* geometryPath) {
	//	return loadedShaders.emplace_back(vertexPath, fragmentPath, geometryPath);
	//}

	/*
	void OpenGLRenderer::internalCameraUpdate(Camera& camera) {
		LOG_FUNCTION();
		for (uint i = 0; i < loadedShaders.size(); i++) {
			  loadedShaders[i].setMat4("pav", camera.perspective * camera.view);
			//loadedShaders[i].setInt("material.diffuse", 0);
			//loadedShaders[i].setInt("material.specular", 0);
			//loadedShaders[i].setFloat("material.shininess", 1.0f);
			//loadedShaders[i].setInt("light[0].lightType", 1);
			//loadedShaders[i].setVec3("light[0].direction", -1.0f, 0.0f, 1.0f);
			//loadedShaders[i].setVec3("light[0].ambient", 0.2f, 0.2f, 0.2f);
			//loadedShaders[i].setVec3("light[0].diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
			//loadedShaders[i].setVec3("light[0].specular", 0.0f, 0.0f, 0.0f);
			//loadedShaders[i].setFloat("light[1].lightType", 0);
			//loadedShaders[i].setFloat("light[2].lightType", 0);
			//loadedShaders[i].setFloat("light[3].lightType", 0);

			//loadedShaders[i].setMat4("projection", camera.perspective);
			//loadedShaders[i].setMat4(   "view"   , camera.view       );
		}
	}
	*/

	void OpenGLRenderer::getDeviceConstantValue(DeviceConstant deviceConstant, void* outputBuffer) {
		auto OpenGLdeviceConstant = OpenGLDeviceConstants.find(deviceConstant);

		glGetIntegerv(OpenGLdeviceConstant->second, (GLint*) outputBuffer);
	}

	void OpenGLRenderer::setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
		glViewport(x, y, width, height);
	}

	int OpenGLRenderer::init() {
		debug_log("[*] Initalizing OpenGL.");

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			debug_log("[!] Initalizing OpenGL failed.");
			return 1;
		}

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		return 0;
	}

	void OpenGLRenderer::renderText(const std::string& text, Transform& transform, Camera& camera, float scale) {
		LOG_FUNCTION();

		auto shader = Shader::load(
			"textShader",
			ReadFile("../Engine/Resources/Shaders/textShader.vert"),
			ReadFile("../Engine/Resources/Shaders/textShader.frag")
		);

		glUseProgram(shader->ID);

		static auto perv = glm::ortho(0.0f, 800.f, 0.0f, 500.f);
		
		{
			LOG_SCOPE("Setting shader vars.");

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
			
			float xpos = x + ch.Bearing.x * scale;
			float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

			float w = ch.Size.x * scale;
			float h = ch.Size.y * scale;

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
			x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
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

		//shader->setFloat( "light[1].lightType", 0 );
		//shader->setFloat( "light[2].lightType", 0 );
		//shader->setFloat( "light[3].lightType", 0 );

		
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