#pragma once

#include <Aliases.h>

namespace PetrolEngine {
    class OpenGLCubemap {
    public:
        OpenGLCubemap(const String& path);
        OpenGLCubemap(
            const String& right,
            const String& left,
            const String& top,
            const String& bottom,
            const String& front,
            const String& back
        );
    };
}
