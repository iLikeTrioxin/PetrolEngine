#include <PCH.h>

#include "Window.h"

namespace PetrolEngine {

    double deltaXMousePos = 0.0;
    double deltaYMousePos = 0.0;
    double cursorXPos     = 0.0;
    double cursorYPos     = 0.0;
    double deltaTime      = 0.0;

    Window* Window::create(WRC* creator, int width, int height, const String& title) {
        return creator->newWindow(width, height, title);
    }

    float Window::getAspectRatio() const {
        return ((float) windowData.width) / ((float)windowData.height);
    }
    
}