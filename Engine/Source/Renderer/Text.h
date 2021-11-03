#pragma once

#include <glm/vec2.hpp>
#include <map>
#include <memory>

namespace PetrolEngine {
    class Texture;

    class Text {
    public:
        struct Character {
            Ref<Texture> texture;  // ID handle of the glyph texture
            glm::ivec2 Size;       // Size of glyph
            glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
            long       Advance;    // Offset to advance to next glyph
        };

        static void init(const std::string& fontPath);
        static Character get(char character);
    private:
        static std::map<char, Character> characters;
    };

}