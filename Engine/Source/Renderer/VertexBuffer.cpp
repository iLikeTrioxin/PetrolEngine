#include <PCH.h>

#include "Renderer.h"

#include "OpenGL/OpenGLVertexBuffer.h"
#include "Vulkan/VulkanVertexBuffer.h"

namespace PetrolEngine {
    Ref<VertexBuffer> VertexBuffer::create(const VertexLayout& layout, const void* data, int64 size) {
		switch (RendererAPI::get())
		{
		    case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexBuffer>(layout, data, size);
            case RendererAPI::API::Vulkan: return CreateRef<VulkanVertexBuffer>(layout, data, size);
            default: return nullptr;
        }
	}

	Ref<VertexBuffer> VertexBuffer::create(const VertexLayout& layout) {
		switch (RendererAPI::get())
        {
		    case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexBuffer>(layout);
            case RendererAPI::API::Vulkan: return CreateRef<VulkanVertexBuffer>(layout);
		    default: return nullptr;
		}
	}
}