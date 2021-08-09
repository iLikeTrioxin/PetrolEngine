#pragma once

#include <glm/vec2.hpp>
#include <map>
#include <memory>

namespace Engine {
    class Texture;

    class Text {
    public:
        struct Character {
            std::shared_ptr<Texture> texture;  // ID handle of the glyph texture
            glm::ivec2   Size;       // Size of glyph
            glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
            unsigned int Advance;    // Offset to advance to next glyph
        };

        static void init(std::string fontPath);
        static Character get(char character);
    private:
        static std::map<char, Character> characters;
    };

}