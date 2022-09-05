#pragma once

#include "Aliases.h"

namespace PetrolEngine {

    class Entity;
    class SystemManager;

	class Scene {
	public:
		Entity* createEntity(const char* name);

        Entity* createGameObject(const char* name, Entity* parent = nullptr);

        Entity* getEntityById(unsigned int id);

        Scene();

		void update();
        void start();
        entt::registry sceneRegistry;

    private:
        Vector<Entity*> entities;
        SystemManager* systemManager;
        friend class Entity;
        friend class SystemManager;
	};
}


