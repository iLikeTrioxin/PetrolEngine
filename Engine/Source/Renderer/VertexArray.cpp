#include <PCH.h>

#include "VertexArray.h"
#include "Renderer.h"
#include "OpenGL/OpenGLVertexArray.h"

namespace PetrolEngine {
	std::shared_ptr<VertexArray> VertexArray::create() {
		switch (RendererAPI::get())
		{
		case RendererAPI::API::None  : return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLVertexArray>();
		}
	}
}