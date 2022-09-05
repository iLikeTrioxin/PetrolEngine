#pragma once

#include "Core/WindowInterface/WindowResourceCreator.h"
#include "GLFWWindow.h"

namespace PetrolEngine {
    class GLFW_: public WindowResourceCreator {
    public:
        WindowI* newWindow(int width, int height, const String& title) override { return new GLFWWindow(width, height, title); }
    } GLFW;
}