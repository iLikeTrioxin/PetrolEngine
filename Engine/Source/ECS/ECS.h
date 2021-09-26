#pragma once

#include <Aliases.h>

namespace PetrolEngine{

    class Entity{

    };

    template<typename T>
    class Component{
        Entity* entity;
    };

    template<typename T>
    class ComponentPool{
    public:
        Vector<T> components;
    };

    // Entity-Component System
    class ECS{
        UnorderedMap<TypeIndex, void*> unorderedMap;

        template<typename T>
        Vector<T> getView(){
            ComponentPool<T>* t = reinterpret_cast<ComponentPool<T>*>( unorderedMap[typeid(T)] );
            return *t;
        }
    };
}