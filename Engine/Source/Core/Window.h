#pragma once

#include <string>
#include <memory>

#include "../Core/Image.h"
#include "EventStack.h"

namespace Engine {

	extern double deltaXMousePos;
	extern double deltaYMousePos;
	extern double cursorXPos;
	extern double cursorYPos;
	
	extern double deltaTime;

	class Window {
	public:
		struct WindowData {
			uint32_t width;
			uint32_t height;

			std::string title;
		};

		struct WindowResizedEvent : Event { WindowData data; WindowResizedEvent(WindowData data) : data(data) {} };
		struct WindowClosedEvent  : Event { WindowData data; WindowClosedEvent (WindowData data) : data(data) {} };

		struct MouseMovedEvent    : Event { double x, y; MouseMovedEvent   (double x, double y) : x(x), y(y) {} };
		struct MouseScrolledEvent : Event { double x, y; MouseScrolledEvent(double x, double y) : x(x), y(y) {} };
		struct MouseClickEvent    : Event { int key; MouseClickEvent(int key) : key(key) {} };
		
		struct KeyPressedEvent  : Event { int key; bool repeat; KeyPressedEvent (int key, bool repeat) : key(key), repeat(repeat) {} };
		struct KeyReleasedEvent : Event { int key;              KeyReleasedEvent(int key             ) : key(key)                 {} };
		struct KeyTypedEvent    : Event { int key;              KeyTypedEvent   (int key             ) : key(key)                 {} };

	public:
		static std::shared_ptr<Window> create(uint32_t width, uint32_t height, std::string title);
		
		uint32_t getWidth () const { return windowData.width ; };
		uint32_t getHeight() const { return windowData.height; };
		
		virtual int  init       () = 0;
		virtual void swapBuffers() = 0;
		virtual bool shouldClose() = 0;
		virtual void close      () = 0;
		virtual void pollEvents () = 0;
		
		virtual void setVSync(bool  enabled) = 0;
		virtual void setIcon (Image image  ) = 0;

		virtual bool isPressed(int key) = 0;

		// Vulkan specific
		virtual void createWindowSurface(void* instance, const void* allocation, void* surface) = 0;

		float getAspectRatio();

	protected:
		WindowData windowData;
	};
}