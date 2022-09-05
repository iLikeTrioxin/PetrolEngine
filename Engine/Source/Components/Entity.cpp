#include "PCH.h"

#include "Components/Entity.h"

#include "Scene.h"

namespace PetrolEngine {
    Entity::Entity(entt::entity entity, Scene* scene): entity(entity), scene(scene) {};

    uint   Entity::getID   () { return (uint) entity; }
	Scene* Entity::getScene() { return        scene ; }
	bool Entity::isValid() {
		return !(entity == entt::null);
	}

}