#pragma once

#include <Aliases.h>

namespace PetrolEngine {

    class ResourceManager {
    public:
        const String& resource(const String& path);

    private:
        UnorderedMap<String, String> resources;
    };

    static ResourceManager programResourceManager;
}

// I prefer to use macro for this as I don't want to make all scripts dependent from it.

#define USE_RESOURCE_MANAGER
#if defined(USE_RESOURCE_MANAGER)
#    define RESOURCE(path) programResourceManager.resource(path)
#else
#    define RESOURCE(path) path
#endif