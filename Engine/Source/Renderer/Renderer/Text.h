#pragma once

#include <Aliases.h>
#include "Core/Logger.h"

#include "glm/vec2.hpp"
#include <map>
#include <memory>

#include "Core/Image.h"

// TODO: integrate Atlas class into FontAtlas or something like that

#include "Renderer/RendererInterface/Texture.h"
#include "../../Atlas.h"

namespace PetrolEngine {
    // this class currently supports only ascii characters
    class Text {
    public:
        struct AtlasCharacter {
            glm::vec4 coords;
            glm::vec2 size;
            glm::vec2 bearing; // Offset from baseline to left/top of glyph
            long  advance; // Offset to advance to next glyph
        };

        struct FontAtlas {
            Atlas<unsigned char>* atlas;
            UnorderedMap<unsigned char, AtlasCharacter> characters;
        };

        static int init();
        static int destroy();
        static int loadFont(const String& fontPath);
        static FontAtlas& getAtlas(const String& font = "../Hei/Resources/Fonts/xd.ttf");//../Hei/Resources/Fonts/Poppins/Poppins-Black.ttf

    private:
        // Map of fonts containing map of characters
        static UnorderedMap<String, FontAtlas> fonts;
    };

}
