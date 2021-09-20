#include "PCH.h"
#include "Entity.h"

#include "Scene.h"
#include "Components.h"

namespace PetrolEngine {
	Entity::Entity(entt::entity _entity, Scene* _scene) :
		entity(_entity), scene(_scene) {};
	entt::entity Entity::getID() {
		return entity;
	}
	Scene* Entity::getScene() {
		return scene;
	}
	bool Entity::isValid() {
		return !(entity == entt::null);
	}
}