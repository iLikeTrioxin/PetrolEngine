#pragma once


namespace Engine {

	class Scene;
	class Entity;
	class Mesh;

	enum textureType;

	class modelLoader
	{
	public:
		Shader* shader;
		static modelLoader& Get();
		static Entity loadModel(const char* _path, Scene*  _scene);
		static Entity loadModel(const char* _path, Entity& _parent);
		
	private:
		static modelLoader modelLoaderInstance;
		static std::mutex mutex;

		void processMesh(aiMesh* mesh, const aiScene* scene, Mesh*  outputMesh);
		void texturesFromMaterial(aiMaterial* material, aiTextureType type, textureType myType, std::vector<Texture>* textures);
		void processNode(aiNode* node, const aiScene* scene, Entity parent);
		std::vector<std::future<void>> meshProcesses;
		
		modelLoader() = default;
	};
}