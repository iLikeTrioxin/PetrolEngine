#include <PCH.h>

#include "Renderer.h"

#include "OpenGL/OpenGLVertexArray.h"
#include "Vulkan/VulkanVertexArray.h"

namespace PetrolEngine {
	Ref<VertexArray> VertexArray::create() {
		switch (RendererAPI::get())
		{
		    case RendererAPI::API::OpenGL: return createRef<OpenGLVertexArray>();
            case RendererAPI::API::Vulkan: return createRef<VulkanVertexArray>();
		    default: return nullptr;
		}
	}
}