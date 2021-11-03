#pragma once

#include <string>
#include <memory>
#include <utility>

#include <Aliases.h>

#include "../Core/Image.h"
#include "EventStack.h"

namespace PetrolEngine {

	extern double deltaXMousePos;
	extern double deltaYMousePos;
	extern double cursorXPos;
	extern double cursorYPos;
	
	extern double deltaTime;

	class Window {
	public:
		struct WindowData {
			int width;
			int height;

			std::string title;
		};

		struct WindowResizedEvent: Event { WindowData data; explicit WindowResizedEvent(WindowData data) : data(std::move(data)) {} };
		struct WindowClosedEvent : Event { WindowData data; explicit WindowClosedEvent (WindowData data) : data(std::move(data)) {} };

		struct MouseMovedEvent   : Event { double x, y; MouseMovedEvent   (double x, double y) : x(x), y(y) {} };
		struct MouseScrolledEvent: Event { double x, y; MouseScrolledEvent(double x, double y) : x(x), y(y) {} };
		struct MouseClickEvent   : Event { int key    ; MouseClickEvent(int key) : key(key) {} };
		
		struct KeyPressedEvent   : Event { int key; bool repeat; KeyPressedEvent (int key, bool repeat) : key(key), repeat(repeat) {} };
		struct KeyReleasedEvent  : Event { int key;              KeyReleasedEvent(int key             ) : key(key)                 {} };
		struct KeyTypedEvent     : Event { int key;              KeyTypedEvent   (int key             ) : key(key)                 {} };

	public:
		static Ref<Window> create(int width, int height, const String& title);
		
		NO_DISCARD int getWidth () const { return windowData.width ; };
		NO_DISCARD int getHeight() const { return windowData.height; };
		
		virtual int  init       () = 0;
		virtual void swapBuffers() = 0;
		virtual bool shouldClose() = 0;
		virtual void close      () = 0;
		virtual void pollEvents () = 0;
		
		virtual void setVSync(bool       enabled) = 0;
		virtual void setIcon (Ref<Image> image  ) = 0;

		virtual bool isPressed(int key) = 0;

		// Vulkan specific
		virtual void createWindowSurface(void* instance, const void* allocation, void* surface) = 0;

		NO_DISCARD float getAspectRatio() const;

	protected:
		WindowData windowData;
	};
}