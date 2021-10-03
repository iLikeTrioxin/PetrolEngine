#include <PCH.h>

#include "Renderer.h"

#include "OpenGL/OpenGLVertexArray.h"
#include "Vulkan/VulkanVertexArray.h"

namespace PetrolEngine {
	std::shared_ptr<VertexArray> VertexArray::create() {
		switch (RendererAPI::get())
		{
		    case RendererAPI::API::OpenGL: return std::make_shared<OpenGLVertexArray>();
            case RendererAPI::API::Vulkan: return std::make_shared<VulkanVertexArray>();
		    default: return nullptr;
		}
	}
}