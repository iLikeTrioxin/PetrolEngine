#pragma once


#include "Scene.h"

#include "Window.h"
#include "Shader.h"
#include "Entity.h"

namespace Engine {
	
	class Scene;
	class Camera;

	extern double deltaXMousePos;
	extern double deltaYMousePos;
	extern double cursorXPos    ;
	extern double cursorYPos    ;
	extern double deltaTime     ;

	extern Entity mainCamera;

	class Game {
	public:
		Window  window;

		std::vector<Scene > scenes;
		
		Game();
		int initalizeGLEW();
		void gameLoop();
	};
}