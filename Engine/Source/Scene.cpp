#include <PCH.h>

#include "Scene.h"
#include "Renderer/Renderer/Renderer.h"
#include "Core/WindowInterface/WindowI.h"
#include "Components/Entity.h"
#include "DebugTools.h"

#include "Components/Entity.h"
#include "Components/Transform.h"
#include "Components/Mesh.h"
#include "Components/Camera.h"
#include "Components/Properties.h"

namespace PetrolEngine {
	Entity* Scene::createEntity(const char* name) {
        entities.push_back(new Entity(
            sceneRegistry.create(),
            this
        ));

        Entity* entity = entities.back();

        entity->addComponent<Properties>(name);

        return entity;
	}

    Entity* Scene::createGameObject(const char* name, Entity* parent) {
        Entity* entity = createEntity(name);

        auto& transform = entity->addComponent<Transform>();

        if (entity->scene == nullptr) {
            LOG("Entity has no scene", 2);
            throw std::runtime_error("Entity has no scene");
        }

        if (parent)
            transform.parent = &parent->getComponent<Transform>();

        return entity;
    }

	Entity* Scene::getEntityById(uint id) {
        for (auto* entity : entities)
            if (entity->getID() == id) return entity;

        return nullptr;
	}

    Scene::Scene() {
        systemManager = new SystemManager();
        systemManager->scene = this;
    }

    void Scene::start(){

    }

	void Scene::update() { LOG_FUNCTION();
		auto camerasGroup = sceneRegistry.group<Camera>(entt::get<Transform>);
		auto meshesGroup  = sceneRegistry.group< Mesh >(entt::get<Transform>);

		for (auto cameraID : camerasGroup) { LOG_SCOPE("Processing camera view");
			auto& cam = camerasGroup.get<Camera>(cameraID);

            cam.updateView();
			
			for (auto& entity : meshesGroup) {
				LOG_SCOPE("Rendering mesh");

				auto& mesh      = meshesGroup.get<   Mesh  >(entity);
				auto  transform = meshesGroup.get<Transform>(entity);

                Transform t = transform.getRelativeTransform();

				Renderer::renderMesh(mesh, t);
			}
			
		}

        systemManager->update();
    }
}