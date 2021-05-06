#pragma once

#include <string>
#include <memory>

namespace Engine {
	
	};
	class FramebufferImageFormat {
	public:
		enum class Formats{
			None,

			// Depth
			DEPTH16,
			DEPTH24,
			DEPTH32,
			DEPTH32F,

			// Stencil
			STENCIL8,
			
			// Depth and stencil
			DEPTH24_STENCIL8,
			DEPTH32F_STENCIL8

		} format;
	};
	class Framebuffer {
	public:

	};
}