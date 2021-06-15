#pragma once

#include <string>
#include <memory>

namespace Engine {

	extern double deltaXMousePos;
	extern double deltaYMousePos;
	extern double cursorXPos;
	extern double cursorYPos;
		
	class Window {
	public:
		struct WindowData {
			uint32_t width;
			uint32_t height;
			std::string title;
		};

	public:
		WindowData windowData;
		double deltaTime;

		static std::unique_ptr<Window> create();
		
		virtual int      init       () = 0;
		virtual void     swapBuffers() = 0;
		virtual uint32_t getWidth   () = 0;
		virtual uint32_t getHeight  () = 0;
		
		float getAspectRatio();
	};
}