#pragma once

#include <Aliases.h>

namespace PetrolEngine{

    class Entity{

    };

    class Component{
        Entity* entity;
    };

    // Entity-Component System
    class ECS{
        UnorderedMap<TypeIndex, void*> unorderedMap;

        template<typename T>
        Vector<T> getView(){
            T* t = reinterpret_cast<T*>( unorderedMap[typeid(T)] );
            return t;
        }
    };
}