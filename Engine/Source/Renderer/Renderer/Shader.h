#pragma once

#include "Renderer/RendererInterface/ShaderI.h"

namespace PetrolEngine {
    class Shader{
    public:
        static Ref<ShaderI> load( const String& filePath);
        static Ref<ShaderI> load( const char* name       ,
                                  const char* vertexSrc  ,
                                  const char* fragmentSrc,
                                  const char* geometrySrc  );

        static Ref<ShaderI> create( const char* vertexSrc   = nullptr,
                                    const char* fragmentSrc = nullptr,
                                    const char* geometrySrc = nullptr  );

    private:
        static UnorderedMap<String, Ref<ShaderI>> loadedShaders;
    };
}