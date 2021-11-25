#pragma once

#define GLFW_INCLUDE_VULKAN

#include "../Window.h"
#include <GLFW/glfw3.h>

namespace PetrolEngine {
	class GLFWWindow : public Window {
	public:
		GLFWWindow(int width, int height, const String& title);

		bool shouldClose() override { return glfwWindowShouldClose(window      ); };
		void swapBuffers() override { glfwSwapBuffers             (window      ); };
		void close      () override { glfwSetWindowShouldClose    (window, true); };
		void pollEvents () override { glfwPollEvents              (            ); };

		int init() override;

		void setVSync( bool  enabled) override;
		void setIcon (Image* image  ) override;

		bool isPressed(int key) override { return glfwGetKey(window, key); }

        ~GLFWWindow() override;

		// Vulkan specific
		void createWindowSurface(void* instance, const void* allocation, void* surface) override;

	private:
		GLFWwindow* window;
	};

}