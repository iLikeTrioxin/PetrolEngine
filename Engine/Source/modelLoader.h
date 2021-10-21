#pragma once

#include "Renderer/Texture.h"
#include "Renderer/Shader.h"

#include <future>
#include <assimp/scene.h>

namespace PetrolEngine {

	class Scene;
	class Entity;
	class Mesh;

	class modelLoader
	{
	public:
		std::shared_ptr<Shader> shader;
		static modelLoader& Get();
		static Entity loadModel(const char* _path, Scene*  _scene);
		static Entity loadModel(const char* _path, Entity& _parent);
		
	private:
		static modelLoader modelLoaderInstance;
		static std::mutex mutex;

		void processMesh(aiMesh* mesh, const aiScene* scene, Mesh*  outputMesh);
		void texturesFromMaterial(aiMaterial* material, aiTextureType type, TextureType myType, std::vector< std::shared_ptr<Texture> >* textures);
		void processNode(aiNode* node, const aiScene* scene, Entity parent);
		std::vector<std::future<void>> meshProcesses;
		
		modelLoader() = default;
	};
}