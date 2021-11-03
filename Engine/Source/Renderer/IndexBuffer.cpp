#include <PCH.h>

#include "IndexBuffer.h"
#include "Renderer.h"

#include "OpenGL/OpenGLIndexBuffer.h"
#include "Vulkan/VulkanIndexBuffer.h"

namespace PetrolEngine {
	Ref<IndexBuffer> IndexBuffer::create(const void* data, int64 size) {
		switch (RendererAPI::get())
		{
            case RendererAPI::API::OpenGL: return CreateRef<OpenGLIndexBuffer>(data, size);
            case RendererAPI::API::Vulkan: return CreateRef<VulkanIndexBuffer>(data, size);
		    default: return nullptr;
		}
	}
	Ref<IndexBuffer> IndexBuffer::create() {
		switch (RendererAPI::get())
		{
            case RendererAPI::API::OpenGL: return CreateRef<OpenGLIndexBuffer>();
            case RendererAPI::API::Vulkan: return CreateRef<VulkanIndexBuffer>();
		    default: return nullptr;
		}
	}
}