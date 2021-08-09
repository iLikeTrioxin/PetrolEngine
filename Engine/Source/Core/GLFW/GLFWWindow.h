#pragma once

#include "../../Core/Window.h"
#include <GLFW/glfw3.h>

namespace Engine {
	class GLFWWindow : public Window {
	public:
		GLFWWindow(uint32_t width, uint32_t height, std::string title);

		virtual bool shouldClose() override { return glfwWindowShouldClose(window)  ; };
		virtual void swapBuffers() override { glfwSwapBuffers(window)               ; };
		virtual void close      () override { glfwSetWindowShouldClose(window, true); };
		virtual void pollEvents () override { glfwPollEvents()                      ; };

		virtual int init() override;

		virtual void setVSync(bool  enabled) override;
		virtual void setIcon (Image image  ) override;

		virtual bool isPressed(int key) override { return glfwGetKey(window, key); }

	private:
		GLFWwindow* window;
	};
}