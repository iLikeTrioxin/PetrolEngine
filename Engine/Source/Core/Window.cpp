#include "../PCH.h"
#include "Window.h"
#include "../Renderer/Renderer.h"
#include "GLFW/GLFWWindow.h"

namespace Engine {

    double deltaXMousePos = 0.0;
    double deltaYMousePos = 0.0;
    double cursorXPos     = 0.0;
    double cursorYPos     = 0.0;

    std::unique_ptr<Window> Window::create() {
        switch ( RendererAPI::get() )
        {
            case RendererAPI::API::None  : return nullptr                       ; break;
            case RendererAPI::API::OpenGL: return std::make_unique<GLFWWindow>(); break;
        }
    }

    float Window::getAspectRatio() {
        return windowData.height / windowData.width;
    }
    
}