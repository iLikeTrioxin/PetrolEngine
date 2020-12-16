#pragma once

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

namespace Engine {
	class Window {
	public:
		GLFWwindow* windowHandle;

		int WIDTH = 800;
		int HEIGHT = 450;

		Window();

		int createWindowAndContent();
		float getAspectRatio();
		void getActualWindowSize();
	};
}