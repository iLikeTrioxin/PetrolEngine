#include "../PCH.h"

#include "GraphicsContext.h"
#include <memory>
#include "Renderer.h"
#include "OpenGL/OpenGLContext.h"

namespace Engine {
	std::unique_ptr<GraphicsContext> GraphicsContext::create(void* window) {
		switch (RendererAPI::get())
		{
			case RendererAPI::API::None  : return nullptr;
			case RendererAPI::API::OpenGL: return std::make_unique<OpenGLContext>();
		}
	}
}