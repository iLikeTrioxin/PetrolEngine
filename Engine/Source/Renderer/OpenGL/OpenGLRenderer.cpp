#include "../../PCH.h"

#include "OpenGLRenderer.h"
#include "../Texture.h"

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

	void OpenGLRenderer::setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
		glViewport(x, y, width, height);
	}

	int OpenGLRenderer::init() {
		debug_log("[*] Initalizing OpenGL.");

		if (!gladLoadGL()) {
			debug_log("[!] Initalizing OpenGL failed.");
			return 1;
		}

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_DEPTH_BUFFER_BIT);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		return 0;
	}

	void OpenGLRenderer::renderMesh(Mesh& mesh, Transform& transform, Camera& camera) {
		LOG_FUNCTION();

		auto shader = mesh.material.shader;

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

		shader->setFloat( "light[1].lightType", 0 );
		shader->setFloat( "light[2].lightType", 0 );
		shader->setFloat( "light[3].lightType", 0 );

		glUseProgram(shader->ID);
		
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
			
			glActiveTexture(GL_TEXTURE0 + textureIndex);
			glBindTexture(GL_TEXTURE_2D, texture->getID());

			switch (texture->type)
			{
			case TextureType::DIFFUSE:
				shader->setInt("texture_diffuse" + diffuseNumber, textureIndex);
				break;
			case TextureType::HEIGHT:
				shader->setInt("texture_height" + heightNumber, textureIndex);
				break;
			case TextureType::NORMAL:
				shader->setInt("texture_normal" + normalNumber, textureIndex);
				break;
			case TextureType::SPECULAR:
				shader->setInt("texture_specular" + specularNumber, textureIndex);
				break;
			default:
				break;
			}
		}

		glBindVertexArray(mesh.getVAO());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.getEBO());
		glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, nullptr);

		//resetBuffers();

	}
	
	void OpenGLRenderer::clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRenderer::resetBuffers() {
		glActiveTexture(GL_TEXTURE0);
	}
}