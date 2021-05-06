#pragma once

#include "../../Core/Window.h"
#include <GLFW/glfw3.h>

namespace Engine {
	class GLFWWindow : public Window {
	public:
		uint32_t getWidth   () override { return windowData.width ; };
		uint32_t getHeight  () override { return windowData.height; };
		void     swapBuffers() override { glfwSwapBuffers(window) ; };

		int init() override;
	private:
		GLFWwindow* window;
	};
}