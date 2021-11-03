#pragma once

#include <Aliases.h>

namespace PetrolEngine {

    class ResourceManager {
    public:
        const String& resource(const String& path);

    private:
        UnorderedMap<String, String> resources;

        String pwd; // current working directory
    };
}

// I prefer to use macro for this as I don't want to make all scripts dependent from it.

#if defined(USE_RESOURCE_MANAGER)
#    define RESOURCE(path) x
#else
#    define RESOURCE(path)
#endif