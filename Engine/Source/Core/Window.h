#pragma once

#include <string>
#include <memory>

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
		
		struct KeyTypedEvent    : Event { int key; KeyTypedEvent   (int key) : key(key) {} };
		struct KeyPressedEvent  : Event { int key; KeyPressedEvent (int key) : key(key) {} };
		struct KeyReleasedEvent : Event { int key; KeyReleasedEvent(int key) : key(key) {} };
		struct KeyHoldenEvent   : Event { int key; KeyHoldenEvent  (int key) : key(key) {} };

	public:
		WindowData windowData;
		
		static std::shared_ptr<Window> create(uint32_t width, uint32_t height, std::string title);
		
		virtual int      init       () = 0;
		virtual void     swapBuffers() = 0;
		virtual uint32_t getWidth   () = 0;
		virtual uint32_t getHeight  () = 0;
		virtual bool     shouldClose() = 0;
		virtual void     close      () = 0;
		virtual void     pollEvents () = 0;

		virtual bool isPressed(int key) = 0;
		
		float getAspectRatio();
	};
}