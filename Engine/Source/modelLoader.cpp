#include "PCH.h"
#include "modelLoader.h"

#include "Components.h"
#include "Scene.h"
#include "./Renderer/Texture.h"
#include "Entity.h"

namespace Engine {

	std::mutex modelLoader::mutex;
	modelLoader modelLoader::modelLoaderInstance;

	modelLoader& modelLoader::Get() {
		return modelLoaderInstance;
	}

	Entity modelLoader::loadModel(const char* _path, Scene* _scene) {
		auto pPath = std::filesystem::current_path();
		auto path  = std::filesystem::path(_path);
		
		auto filename   = path.filename().string();
		auto workingDir = path.remove_filename();

		std::filesystem::current_path(path);

		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(filename, aiProcess_GenSmoothNormals | aiProcess_Triangulate);
		//  aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
			std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
			return Entity();
		}

		debug_log("[*] Running down the Root node of model(" << _path << ")");
	
		Entity model = _scene->createEntity(filename.c_str());

		modelLoaderInstance.processNode(scene->mRootNode, scene, model);

		for (uint i = 0; i < modelLoaderInstance.meshProcesses.size(); i++) {
			modelLoaderInstance.meshProcesses[i].wait();
		}

		modelLoaderInstance.meshProcesses.clear();

		std::filesystem::current_path(pPath);

		return model;
	}
	Entity modelLoader::loadModel(const char* _path, Entity& _parent) {

		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(_path, aiProcess_GenNormals);
		//  aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
			std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
			return Entity();
		}

		debug_log("[*] Running down the Root node of model(" << _path << ")");

		std::string fileName(_path);

		Entity model = _parent.getScene()->createEntity(fileName.substr(fileName.find_last_of("\\/") + 1).c_str(), _parent.getID());

		modelLoaderInstance.processNode(scene->mRootNode, scene, model);

		for (uint i = 0; i < modelLoaderInstance.meshProcesses.size(); i++) {
			modelLoaderInstance.meshProcesses[i].wait();
		}

		modelLoaderInstance.meshProcesses.clear();

		return model;
	}
	void modelLoader::texturesFromMaterial(aiMaterial* material, aiTextureType type, TextureType myType, std::vector< std::shared_ptr<Texture> >* textures) {
		debug_log("[*] Detected " << material->GetTextureCount(type) << " textures of " << myType);

		for (uint i = 0; i < (material->GetTextureCount(type)); i++) {
			aiString path;
			material->GetTexture(type, i, &path);
			auto tex = Texture::create(std::string(path.C_Str()), myType);
			textures->push_back(tex);
		}
	}
	
	void modelLoader::processMesh(aiMesh* mesh, const aiScene* scene, Mesh* outputMesh) {
		std::lock_guard<std::mutex> lock(mutex);
		outputMesh->vertices.reserve(mesh->mNumVertices);
		outputMesh->indices .reserve(mesh->mNumVertices);
		
		outputMesh->material.shader = shader;

		for (uint i = 0; i < mesh->mNumVertices; i++) {
			{
				outputMesh->vertices.emplace_back();
			}
			//debug_log("[can i] i: " << i << " and vert: " << outputMesh->vertices.size());

			outputMesh->vertices[i].position.x = mesh->mVertices[i].x;
			outputMesh->vertices[i].position.y = mesh->mVertices[i].y;
			outputMesh->vertices[i].position.z = mesh->mVertices[i].z;
			
			if (mesh->HasNormals()) {
				outputMesh->vertices[i].normal.x = mesh->mNormals[i].x;
				outputMesh->vertices[i].normal.y = mesh->mNormals[i].y;
				outputMesh->vertices[i].normal.z = mesh->mNormals[i].z;
			}
			if (mesh->mTextureCoords[0]) {
				outputMesh->vertices[i].texCoords.x = mesh->mTextureCoords[0][i].x;
				outputMesh->vertices[i].texCoords.y = mesh->mTextureCoords[0][i].y;
			}
			else
			{
				outputMesh->vertices[i].texCoords.x = 0.0f;
				outputMesh->vertices[i].texCoords.y = 0.0f;
			}
			if (mesh->HasTangentsAndBitangents()) {
				outputMesh->vertices[i].tangent.x = mesh->mTangents[i].x;
				outputMesh->vertices[i].tangent.y = mesh->mTangents[i].y;
				outputMesh->vertices[i].tangent.z = mesh->mTangents[i].z;

				outputMesh->vertices[i].bitangent.x = mesh->mBitangents[i].x;
				outputMesh->vertices[i].bitangent.y = mesh->mBitangents[i].y;
				outputMesh->vertices[i].bitangent.z = mesh->mBitangents[i].z;
			}
		}
		
		for (uint i = 0; i < mesh->mNumFaces; i++) {
			aiFace face = mesh->mFaces[i];

			for (uint j = 0; j < face.mNumIndices; j++) {
				outputMesh->indices.emplace_back(face.mIndices[j]);
			}
		}
		
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		{
			texturesFromMaterial(material, aiTextureType_DIFFUSE , TextureType::DIFFUSE , &outputMesh->material.textures);
			texturesFromMaterial(material, aiTextureType_AMBIENT , TextureType::HEIGHT  , &outputMesh->material.textures);
			texturesFromMaterial(material, aiTextureType_HEIGHT  , TextureType::NORMAL  , &outputMesh->material.textures);
			texturesFromMaterial(material, aiTextureType_SPECULAR, TextureType::SPECULAR, &outputMesh->material.textures);
		}
		outputMesh->initalizeBuffers();
		outputMesh->fillBufferWithData();
		
		//debug_log("done 1");
		//debug_log("[*] Textures: " << scene->HasTextures() << " -- " << scene->mNumTextures);
	}
	void modelLoader::processNode(aiNode* node, const aiScene* _scene, Entity parent) {
		for (uint i = 0; i < node->mNumMeshes; i++) {
			aiMesh* _mesh_ = _scene->mMeshes[node->mMeshes[i]];
			const char* name = (node->mName.length == 0) ? "New node" : node->mName.C_Str();

			Scene* scene = parent.getScene();
			Entity meshEntity = scene->createEntity(name, parent.getID());
			Mesh*  mesh = &meshEntity.addComponent<Mesh>();
			
			modelLoader::Get().processMesh(_mesh_, _scene, mesh);
			//meshProcesses.push_back(std::move(std::async([](aiMesh* mesh, const aiScene* scene, Mesh* outputMesh) {modelLoader::Get().processMesh(mesh, scene, outputMesh);}, _mesh_, _scene, mesh)));
			//meshProcesses.back().wait();
		}
		for (uint i = 0; i < node->mNumChildren; i++) {
			processNode(node->mChildren[i], _scene, parent);
		}
	}
}