#pragma once

#include "Aliases.h"

#include "Core/WindowInterface/WindowI.h"

namespace PetrolEngine{
    class WindowI;

    class WindowResourceCreator {
    public:
        virtual WindowI* newWindow(int width, int height, const String& title) = 0;
    };

    using WRC = PetrolEngine::WindowResourceCreator;
}