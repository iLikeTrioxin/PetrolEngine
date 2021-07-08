#pragma once

#include "../../Core/Window.h"
#include <GLFW/glfw3.h>

namespace Engine {
	class GLFWWindow : public Window {
	public:
		GLFWWindow(uint32_t width, uint32_t height, std::string title);

		virtual uint32_t getWidth   () override { return windowData.width ; };
		virtual uint32_t getHeight  () override { return windowData.height; };
		virtual bool     shouldClose() override { return glfwWindowShouldClose(window); };
		virtual void     swapBuffers() override { glfwSwapBuffers(window); };
		virtual void     close      () override { glfwSetWindowShouldClose(window, true); }
		virtual int      init       () override;
		virtual void     pollEvents () override { glfwPollEvents(); }

		virtual bool isPressed(int key) override { return glfwGetKey(window, key); }

	private:
		GLFWwindow* window;
	};
}