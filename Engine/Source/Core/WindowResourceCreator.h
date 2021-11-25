#pragma once

#include <Aliases.h>

#include "Window.h"

namespace PetrolEngine{
    class Window;

    class WindowResourceCreator {
    public:
        virtual Window* newWindow(int width, int height, const String& title) = 0;
    };

    using WRC = PetrolEngine::WindowResourceCreator;
}