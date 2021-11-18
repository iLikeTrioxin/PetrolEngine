#include <PCH.h>

#include "ResourceManager.h"
#include <filesystem>

namespace PetrolEngine{
    ResourceManager programResourceManager = ResourceManager();

    const String& ResourceManager::resource(const String& path) {
        auto resource = resources.find(path);

        if (resource != resources.end()) return resource->second;

        //resources[path] = std::filesystem::absolute(path);
    }

}