#pragma once

#include "Aliases.h"

namespace PetrolEngine {
    class Transform;
    class Entity;

    class InternalComponent {
    public:
        Entity* entity = nullptr;
    };

    class NativeComponent: public InternalComponent {
    public:
        uint64 typeId;
    };

    class Component: public InternalComponent {
    public:
        Transform* transform = nullptr;

        virtual void onStart()  {};
        virtual void onUpdate() {};

        // function used in debug mode to check if entity has required components
        virtual void preValidate() {};
    };
}