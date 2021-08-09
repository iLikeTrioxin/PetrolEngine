#include <PCH.h>

#include "IndexBuffer.h"
#include "Renderer.h"

#include "OpenGL/OpenGLIndexBuffer.h"

namespace Engine {
	std::shared_ptr<IndexBuffer> IndexBuffer::create(void* data, uint32_t size) {
		switch (RendererAPI::get())
		{
		case RendererAPI::API::None: return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLIndexBuffer>(data, size);
		}
	}
	std::shared_ptr<IndexBuffer> IndexBuffer::create() {
		switch (RendererAPI::get())
		{
		case RendererAPI::API::None: return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLIndexBuffer>();
		}
	}
}