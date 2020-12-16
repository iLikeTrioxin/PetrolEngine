#include "PrecompiledHeader.h"
#include "Scene.h"
#include "Renderer.h"
#include "Components.h"
#include "Window.h"
#include "Entity.h"

namespace Engine {
	Entity Scene::createEntity(const char* name) {
		Entity entity = { sceneRegistry.create(), this };
		
		entity.addComponent<Transform>();
		entity.addComponent<   Tag   >( name == "" ? "New entity" : name, entt::null );

		return entity;
	}
	Entity Scene::createEntity(const char* name, entt::entity parent) {
		Entity entity = { sceneRegistry.create(), this };

		entity.addComponent<Transform>();
		entity.addComponent<   Tag   >( name == "" ? "New entity" : name, parent );
		
		return entity;
	}
	Entity Scene::getEntityById(uint id) {
		return Entity((entt::entity)id, this);
	}
	void Scene::update() {
		
		auto cameras = sceneRegistry.group<Camera>(entt::get<Transform>);
		auto meshes  = sceneRegistry.group< Mesh >(entt::get<Transform>);
		
		for (auto camera : cameras) {
			auto& cam = cameras.get<  Camera >(camera);
			auto& tra = cameras.get<Transform>(camera);

			cam.updatePerspectiveMatrix(Renderer::getWindow()->getAspectRatio());
			cam.updateViewMatrix       (tra.position);
			
			Renderer::updateCamera(cam);

			for (auto entity : meshes) {
				auto& mesh      = meshes.get<   Mesh  >(entity);
				auto  transform = meshes.get<Transform>(entity);
				auto  parent    = sceneRegistry.get<   Tag   >(entity).parent;
				
				if (parent != entt::null) {
					transform += sceneRegistry.get<Transform>(parent);
				}

				transform.updateTransformMatrix();
				
				Renderer::renderMesh(mesh, transform);
			}
		}
	}
}