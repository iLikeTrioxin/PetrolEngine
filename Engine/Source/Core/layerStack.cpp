#include "../PCH.h"
#include "Window.h"
#include "../Renderer/Renderer.h"
#include "GLFW/GLFWWindow.h"

namespace Engine {
    std::unique_ptr<Window> create() {
        switch (RendererAPI::get())
        {
            case RendererAPI::API::None  : return nullptr;
            case RendererAPI::API::OpenGL: return std::make_unique<GLFWWindow>();
        }
    }
}