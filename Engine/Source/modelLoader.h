#pragma once

#include "Renderer/Texture.h"
#include "Renderer/Shader.h"

#include <future>
#include <assimp/scene.h>

namespace PetrolEngine {

	class Scene;
	class Entity;
	class Mesh;

	class ModelLoader
	{
	public:
		Ref<Shader> shader;
		static ModelLoader& Get();
		static Entity loadModel(const char* _path, Scene*  _scene);
		static Entity loadModel(const char* _path, Entity& _parent);
		
	private:
		static ModelLoader modelLoader;
		static std::mutex mutex;

		void processMesh(aiMesh* mesh, const aiScene* scene, Mesh*  outputMesh) const;
		static void texturesFromMaterial(aiMaterial* material, aiTextureType type, TextureType myType, std::vector< Ref<Texture> >* textures);
		void processNode(aiNode* node, const aiScene* scene, Entity parent);
		std::vector<std::future<void>> meshProcesses;
		
		ModelLoader() = default;
	};
}