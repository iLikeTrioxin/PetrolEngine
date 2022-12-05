#include <PCH.h>

#include "Renderer.h"
#include "defaultShaders.h"

namespace PetrolEngine {
    // Renderer singleton variables
    const Camera* Renderer::camera;
    RendererAPI*  Renderer::renderer;
    RRC*          Renderer::creator;

    UnorderedMap<RRC*, RendererResources*> Renderer::rendererResourcesCache;
    RendererResources*                     Renderer::rendererResources;

    auto getSourcesFromString(String fileSource, String keyword = "#type") {
        UnorderedMap<String, String> sources;

        String lcSource; // lower case source because find would detect only lower case "#type"

        lcSource.resize(fileSource.length());

        // copy fileSource to lcSource while lowering case and lower keyword directly
        std::transform(fileSource.begin(), fileSource.end(), lcSource.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        std::transform(keyword.begin(), keyword.end(), keyword.begin(),
                       [](unsigned char c) { return std::tolower(c); });

        for (std::size_t keyPos = lcSource.find(keyword); keyPos != std::string::npos;) {
            std::size_t nextKeyPos = lcSource.find(keyword, keyPos + keyword.length());

            std::size_t endOfKeyPos = keyPos + keyword.length() + 1;
            std::size_t endOfTypeLine = lcSource.find("\r\n", endOfKeyPos);

            std::string type = lcSource.substr(endOfKeyPos, endOfTypeLine - endOfKeyPos);

            sources[type] = fileSource.substr(endOfTypeLine, nextKeyPos - endOfTypeLine);

            keyPos = nextKeyPos;
        }

        return sources;
    }


    Ref<Shader> Renderer::loadShader(const String& path) {
        // check if shader with that path wasn't already loaded
        auto isShaderInHash = rendererResources->shaders.find(path);

        if (isShaderInHash != rendererResources->shaders.end())
            return isShaderInHash->second;

        // Read file content and get separated sources
        auto sources(getSourcesFromString(ReadFile(path)));

        // list of strings with names of valid shader types
        std::string shaders[3] = {"vertex", "fragment", "geometry"};

        // iterate thought every shader and replace shader name
        // with source code if defined or empty string if not
        for(auto& shader : shaders){
            auto source = sources.find(shader);

            shader = (source == sources.end()) ? "" : std::move(source->second);
        }

        // create shader from corresponding sources and store it
        auto shader = Renderer::createShader(      path.c_str(),
                                             shaders[0].c_str(),
                                             shaders[1].c_str(),
                                             shaders[2].c_str() );

        // add shader to unordered map to not clone it in future
        rendererResources->shaders[path] = shader;

        return shader;
    }



    Ref<Shader> Renderer::loadShader(const String& name       ,
                                     const String& vertexSrc  ,
                                     const String& fragmentSrc,
                                     const String& geometrySrc  ) {
        LOG_FUNCTION();

        // find shader with that name
        auto isShaderInHash = rendererResources->shaders.find(name);

        // if such a shader exists return it and continue if not
        if (isShaderInHash != rendererResources->shaders.end())
            return isShaderInHash->second;

        // create shader with corresponding sources
        auto shader = Renderer::createShader(
                       name,
                  vertexSrc,
                fragmentSrc,
                geometrySrc
        );

        // add it to unordered map to prevent copying
        rendererResources->shaders[name] = shader;

        return shader;
    }
}