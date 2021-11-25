#include "../WindowResourceCreator.h"
#include "GLFWWindow.h"

namespace PetrolEngine{

    class : public WindowResourceCreator {
    public:
        Window* newWindow(int width, int height, const String& title) override { return new GLFWWindow(width, height, title); }
    } GLFW;
}