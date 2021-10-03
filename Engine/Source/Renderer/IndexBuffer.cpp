#include <PCH.h>

#include "IndexBuffer.h"
#include "Renderer.h"

#include "OpenGL/OpenGLIndexBuffer.h"
#include "Vulkan/VulkanIndexBuffer.h"

namespace PetrolEngine {
	std::shared_ptr<IndexBuffer> IndexBuffer::create(void* data, uint32_t size) {
		switch (RendererAPI::get())
		{
            case RendererAPI::API::OpenGL: return std::make_shared<OpenGLIndexBuffer>(data, size);
            case RendererAPI::API::Vulkan: return std::make_shared<VulkanIndexBuffer>(data, size);
		    default: return nullptr;
		}
	}
	std::shared_ptr<IndexBuffer> IndexBuffer::create() {
		switch (RendererAPI::get())
		{
            case RendererAPI::API::OpenGL: return std::make_shared<OpenGLIndexBuffer>();
            case RendererAPI::API::Vulkan: return std::make_shared<VulkanIndexBuffer>();
		    default: return nullptr;
		}
	}
}