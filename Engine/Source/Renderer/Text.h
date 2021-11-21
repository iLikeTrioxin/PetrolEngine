#pragma once

#include <Aliases.h>

#include <glm/vec2.hpp>
#include <map>
#include <memory>

#include "../Core/Image.h"

namespace PetrolEngine {

    class Text {
    public:
        using ivec2 = glm::ivec2;

        struct Character {
            Image* image  ; // Image of the glyph
            ivec2  size   ; // Size of glyph
            ivec2  bearing; // Offset from baseline to left/top of glyph
            long   advance; // Offset to advance to next glyph
        };

        static void init(const String& fontPath);
        static Character get(char character);

    private:
        static UnorderedMap<char, Character> characters;
    };

}