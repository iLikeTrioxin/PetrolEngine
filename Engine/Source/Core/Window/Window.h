#pragma once

#include <string>
#include <memory>
#include <utility>

#include "Aliases.h"

#include "Core/Image.h"
#include "Core/EventStack.h"
#include "../WindowInterface/WindowResourceCreator.h"

namespace PetrolEngine {

	class Window {
	public:
        static void setContext(WRC& creator){
            Window::creator = &creator;
        }

        static int  init(int width, int height, const String& title){
            window = creator->newWindow(width, height, title);
            return window->init();
        };

		static Ref<WindowI> create(int width, int height, const String& title);

        NO_DISCARD static int getWidth () { return window->getWidth(); };
		NO_DISCARD static int getHeight() { return window->getHeight(); };

		static void swapBuffers() { return window->swapBuffers(); };
        static bool shouldClose() { return window->shouldClose(); };
		static void close      () { return window->close(); };
        static void pollEvents () { return window->pollEvents(); };
        static void showCursor(bool x) { return window->showCursor(x); };

		static void setVSync(bool   enabled) {return window->setVSync(enabled); };
        static void setIcon (Image* image  ) {return window->setIcon(image); };
        static void setIcon (String path  ) {
            Image* iconImage = Image::create(path);
            window->setIcon(iconImage);
            delete iconImage;
        };

		static bool isPressed(int key) { return window->isPressed(key); };

        ~Window() = default;

		// Vulkan specific
		static void createWindowSurface(void* instance, const void* allocation, void* surface) { return window->createWindowSurface(instance, allocation, surface); };

        static float getAspectRatio() {return window->getAspectRatio(); };

	private:
        static WRC* creator;
        static WindowI* window;
	};
}