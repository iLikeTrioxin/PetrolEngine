#pragma once

#include "EnTT/single_include/entt/entt.hpp"

namespace Engine
{
	class Entity;
	class Window;
	class Renderer;
	
	class Scene
	{
	public:
		Entity createEntity (const char* name                     );
		Entity createEntity (const char* name, entt::entity parent);
		Entity getEntityById(unsigned int id);
		void update(float a);

		entt::registry sceneRegistry;
	private:
		friend class Entity;
	};
}


