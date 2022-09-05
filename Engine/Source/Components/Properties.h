#pragma once

#include "Components/Component.h"

namespace PetrolEngine {
    class Properties: public InternalComponent {
    public:
        const char* name = nullptr;

        Properties() = default;
        Properties(const char* name): name(name) {}

    };
}