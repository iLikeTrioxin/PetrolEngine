#include "../PCH.h"
#include "Renderer.h"

#include "OpenGL/OpenGLRenderer.h"

#include "../Components.h"
#include "../Core/Window.h"
#include "../DebugTools.h"

namespace Engine {
	std::unique_ptr<RendererAPI> Renderer::rendererAPI;
	
	Renderer Renderer::renderer;
	RendererAPI::API RendererAPI::currentAPI = RendererAPI::API::OpenGL;

	std::unique_ptr<RendererAPI> RendererAPI::create() {
		switch (currentAPI)
		{
		case API::None  : return nullptr;                            break;
		case API::OpenGL: return std::make_unique<OpenGLRenderer>(); break;
		}

		return nullptr;
	}
	
}