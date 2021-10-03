#include <PCH.h>

#include "Renderer.h"

#include "OpenGL/OpenGLVertexBuffer.h"
#include "Vulkan/VulkanVertexBuffer.h"

namespace PetrolEngine {
    std::shared_ptr<VertexBuffer> VertexBuffer::create(const VertexLayout& layout, void* data, uint32_t size) {
		switch (RendererAPI::get())
		{
		    case RendererAPI::API::OpenGL: return std::make_shared<OpenGLVertexBuffer>(layout, data, size);
            case RendererAPI::API::Vulkan: return std::make_shared<VulkanVertexBuffer>(layout, data, size);
            default: return nullptr;
        }
	}

	std::shared_ptr<VertexBuffer> VertexBuffer::create(const VertexLayout& layout) {
		switch (RendererAPI::get())
        {
		    case RendererAPI::API::OpenGL: return std::make_shared<OpenGLVertexBuffer>(layout);
            case RendererAPI::API::Vulkan: return std::make_shared<VulkanVertexBuffer>(layout);
		    default: return nullptr;
		}
	}
}