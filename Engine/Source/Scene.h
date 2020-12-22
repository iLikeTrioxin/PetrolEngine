#pragma once

#include "EnTT/single_include/entt/entt.hpp"

namespace Engine
{
	static class Entity;
	static class Window;
	static class Renderer;
	
	class Scene
	{
	public:
		Entity createEntity (const char* name                     );
		Entity createEntity (const char* name, entt::entity parent);
		Entity getEntityById(uint id);
		void update();

		entt::registry sceneRegistry;
	private:
		friend class Entity;
	};
}


