#include "../../PCH.h"

#include "OpenGLRenderer.h"

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
	void Renderer::internalCameraUpdate(Camera& camera) {
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
	void Renderer::renderMesh(Mesh& mesh, Transform& transform) {
		LOG_FUNCTION();

		// Applying them to shader used by mesh
		mesh.material.shader->setMat4("model", transform.transformation);
		
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

			Texture& texture = mesh.material.textures[textureIndex];
			
			glActiveTexture(GL_TEXTURE0 + textureIndex);
			glBindTexture(GL_TEXTURE_2D, texture.id);

			switch (texture.type)
			{
			case textureType::DIFFUSE:
				mesh.material.shader->setInt("texture_diffuse" + diffuseNumber, textureIndex);
				break;
			case textureType::HEIGHT:
				mesh.material.shader->setInt("texture_height" + heightNumber, textureIndex);
				break;
			case textureType::NORMAL:
				mesh.material.shader->setInt("texture_normal" + normalNumber, textureIndex);
				break;
			case textureType::SPECULAR:
				mesh.material.shader->setInt("texture_specular" + specularNumber, textureIndex);
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
	void Renderer::resetBuffers() {
		glActiveTexture(GL_TEXTURE0);
	}
}