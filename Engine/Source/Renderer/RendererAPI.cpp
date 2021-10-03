#include "RendererAPI.h"

#include "OpenGL/OpenGLRenderer.h"
#include "Vulkan/VulkanRenderer.h"

namespace PetrolEngine{

    RendererAPI::API RendererAPI:: currentAPI = RendererAPI::API::None;

    Ptr<RendererAPI> RendererAPI::create(API targetAPI) {
        currentAPI = targetAPI;
        switch (targetAPI)
        {
            case API::OpenGL: return std::make_unique<OpenGLRenderer>();
            case API::Vulkan: return std::make_unique<VulkanRenderer>();
            default         : return nullptr;
        }
    }
}