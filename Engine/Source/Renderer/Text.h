#pragma once

#include <glm/vec2.hpp>
#include <map>
#include "Texture.h"
#include <memory>
#include <Aliases.h>

namespace PetrolEngine {

    class Text {
    public:
        struct Character {
            Texture*   texture; // ID handle of the glyph texture
            glm::ivec2 Size   ; // Size of glyph
            glm::ivec2 Bearing; // Offset from baseline to left/top of glyph
            long       Advance; // Offset to advance to next glyph
        };

        static void init(const String& fontPath);
        static Character get(char character);
    private:
        static UnorderedMap<char, Character> characters;
    };

}