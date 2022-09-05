#pragma once

#include "Renderer/RendererInterface/TextureI.h"
#include "Renderer/RendererInterface/ShaderI.h"
#include "Components/Mesh.h"

#include <future>
#include <assimp/scene.h>

namespace PetrolEngine {

	class Scene;
	class Entity;
	class Mesh;

	class ModelLoader
	{
	public:
		Ref<ShaderI> shader;
		static ModelLoader& Get();
		static Entity* loadModel(const char* path, Scene*  scene);
		static Entity* loadModel(const char* path, Entity* parent);
		
	private:
		static ModelLoader modelLoader;
		static std::mutex mutex;

		void processMesh(aiMesh* mesh, const aiScene* scene, Mesh*  outputMesh) const;
		static void texturesFromMaterial(aiMaterial* material, aiTextureType type, Vector< Ref<TextureI> >* textures);
		void processNode(aiNode* node, const aiScene* scene, Entity* parent);
		//std::vector<std::future<void>> meshProcesses;
		
		ModelLoader() = default;
	};
}


