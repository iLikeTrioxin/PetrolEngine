#pragma once


#include "Scene.h"

#include "./Core/Window.h"
#include "./Renderer/Shader.h"
#include "Entity.h"

namespace Engine {
	extern Entity mainCamera;

	class Game {
	public:
		std::unique_ptr<Window>  window = Window::create();

		std::vector<Scene> scenes;
		
		Game();
		int initalizeGLEW();
		void gameLoop();
	};
}