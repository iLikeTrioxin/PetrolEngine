#include <PCH.h>

#include "IndexBuffer.h"
#include "Renderer.h"

#include "OpenGL/OpenGLIndexBuffer.h"
#include "Vulkan/VulkanIndexBuffer.h"

namespace PetrolEngine {
	Ref<IndexBuffer> IndexBuffer::create(const void* data, int64 size) {
		switch (RendererAPI::get())
		{
            case RendererAPI::API::OpenGL: return createRef<OpenGLIndexBuffer>(data, size);
            case RendererAPI::API::Vulkan: return createRef<VulkanIndexBuffer>(data, size);
		    default: return nullptr;
		}
	}
	Ref<IndexBuffer> IndexBuffer::create() {
		switch (RendererAPI::get())
		{
            case RendererAPI::API::OpenGL: return createRef<OpenGLIndexBuffer>();
            case RendererAPI::API::Vulkan: return createRef<VulkanIndexBuffer>();
		    default: return nullptr;
		}
	}
}