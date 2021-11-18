#pragma once

#include <Aliases.h>

namespace PetrolEngine{
    class Window;

    class WindowResourceCreator {
    public:
        virtual Window* newWindow(int width, int height, String&& title) = 0;
    };

    using WRC = PetrolEngine::WindowResourceCreator;
}