#include "PCH.h"

#include "Window.h"

namespace PetrolEngine {

    double deltaXMousePos = 0.0;
    double deltaYMousePos = 0.0;
    double cursorXPos     = 0.0;
    double cursorYPos     = 0.0;
    double deltaTime      = 0.0;

    WRC* Window::creator;
    WindowI* Window::window;

    Ref<WindowI> Window::create(int width, int height, const String& title) {
        return Ref<WindowI>(creator->newWindow(width, height, title));
    }
    
}