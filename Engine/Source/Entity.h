#pragma once

#include "Scene.h"
#include <entt/entt.hpp>

namespace PetrolEngine {

	class Scene;

	class Entity
	{
	public:
		Entity(entt::entity _entity = entt::null, Scene* _scene = nullptr);

		template<typename T, typename ... Args>
		T& addComponent(Args&&... args) {
			return scene->sceneRegistry.emplace<T>(entity, std::forward<Args>(args)...);
		}

		template<typename T>
		void hasComponent() {
			//scene->sceneRegistry.has<T>(entity);
		}

		template<typename T>
		T& getComponent() {
			return scene->sceneRegistry.get<T>(entity);
		}

		template<typename T>
		void removeComponent() {
			scene->sceneRegistry.remove_if_exists<T>(entity);
		}

		entt::entity getID();
		Scene* getScene();
		bool isValid();

	private:
		entt::entity entity { entt::null };
		Scene*       scene  {   nullptr  };
	};

} 