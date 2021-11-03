#include <PCH.h>

#include "Window.h"
#include "GLFW/GLFWWindow.h"

namespace PetrolEngine {

    double deltaXMousePos = 0.0;
    double deltaYMousePos = 0.0;
    double cursorXPos     = 0.0;
    double cursorYPos     = 0.0;
    double deltaTime      = 0.0;

    Ref<Window> Window::create(int width, int height, const String& title) {
        return CreateRef<GLFWWindow>(width, height, title);
    }

    float Window::getAspectRatio() const {
        return ((float) windowData.width) / ((float)windowData.height);
    }
    
}