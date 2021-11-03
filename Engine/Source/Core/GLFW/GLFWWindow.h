#pragma once

#define GLFW_INCLUDE_VULKAN

#include "../../Core/Window.h"
#include <GLFW/glfw3.h>

namespace PetrolEngine {
	class GLFWWindow : public Window {
	public:
		GLFWWindow(uint32_t width, uint32_t height, std::string title);

		bool shouldClose() override { return glfwWindowShouldClose(window)        ; };
		void swapBuffers() override { glfwSwapBuffers(window)                     ; };
		void close      () override { glfwSetWindowShouldClose(window, true); }; //-V601
		void pollEvents () override { glfwPollEvents()                            ; };

		int init() override;

		void setVSync(bool       enabled) override;
		void setIcon (Ref<Image> image  ) override;

		bool isPressed(int key) override { return glfwGetKey(window, key); }

		// Vulkan specific
		void createWindowSurface(void* instance, const void* allocation, void* surface) override;

	private:
		GLFWwindow* window;
	};
}