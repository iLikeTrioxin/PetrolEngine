#pragma once


#include "Scene.h"

#include "./Core/Window.h"
#include "./Renderer/Shader.h"
#include "Entity.h"

namespace Engine {
	extern Entity mainCamera;

	class Game {
	public:
		std::shared_ptr<Window> window;

		std::vector<Scene> scenes;
		
		Game();

		void gameLoop();
	};
}