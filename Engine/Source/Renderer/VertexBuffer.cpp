#include <PCH.h>

#include "VertexBuffer.h"
#include "Renderer.h"

#include "OpenGL/OpenGLVertexBuffer.h"

namespace Engine {
	std::shared_ptr<VertexBuffer> VertexBuffer::create(VertexLayout layout, void* data, uint32_t size){
		switch (RendererAPI::get())
		{
		case RendererAPI::API::None  : return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLVertexBuffer>(layout, data, size);
		}
	}
	std::shared_ptr<VertexBuffer> VertexBuffer::create(VertexLayout layout) {
		switch (RendererAPI::get())
		{
		case RendererAPI::API::None  : return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLVertexBuffer>(layout);
		}
	}
}