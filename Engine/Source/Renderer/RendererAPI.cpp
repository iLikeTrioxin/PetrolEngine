#include "RendererAPI.h"

#include "OpenGL/OpenGLRenderer.h"
#include "Vulkan/VulkanRenderer.h"

namespace Engine{

    RendererAPI::API RendererAPI:: currentAPI = RendererAPI::API::None;

    Ptr<RendererAPI> RendererAPI::create(API targetAPI) {
        currentAPI = targetAPI;
        switch (targetAPI)
        {
            case API::None  : return nullptr                           ; break;
            case API::OpenGL: return std::make_unique<OpenGLRenderer>(); break;
            case API::Vulkan: return std::make_unique<VulkanRenderer>(); break;
        }
    }
}