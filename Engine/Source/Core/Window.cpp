#include "../PCH.h"
#include "Window.h"
#include "../Renderer/Renderer.h"
#include "GLFW/GLFWWindow.h"

namespace Engine {

    double deltaXMousePos = 0.0;
    double deltaYMousePos = 0.0;
    double cursorXPos     = 0.0;
    double cursorYPos     = 0.0;
    double deltaTime      = 0.0;

    std::shared_ptr<Window> Window::create(uint32_t width, uint32_t height, std::string title) {
        switch ( RendererAPI::get() )
        {
            case RendererAPI::API::OpenGL: return std::make_shared<GLFWWindow>(width, height, title); break;
            default                      : return nullptr                                           ; break;
        }
    }

    float Window::getAspectRatio() {
        return ((float) windowData.width) / ((float)windowData.height);
    }
    
}