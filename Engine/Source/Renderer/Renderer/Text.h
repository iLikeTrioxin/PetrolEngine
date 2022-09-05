#pragma once

#include <Aliases.h>
#include "Core/Logger.h"

#include "glm/vec2.hpp"
#include <map>
#include <memory>

#include "Core/Image.h"

// TODO: integrate Atlas class into FontAtlas or something like that

#include "Renderer/RendererInterface/TextureI.h"

namespace PetrolEngine {

    template<typename T>
    class Atlas {
    public:
        Atlas(int cellSize, int cellCountX, int cellCountY): data(nullptr), cellSize(cellSize), cellCountX(cellCountX), cellCountY(cellCountY) {
            data = new T[cellSize * cellSize * cellCountX * cellCountY];
        }

        NO_DISCARD int getWidth () const { return cellSize * cellCountX; }
        NO_DISCARD int getHeight() const { return cellSize * cellCountY; }

        NO_DISCARD int getCellCountX() const { return cellCountX; }
        NO_DISCARD int getCellCountY() const { return cellCountY; }

        NO_DISCARD int getCellSize() const { return cellSize; }

        NO_DISCARD const T* getData() const { return data; }

        ~Atlas() {
            delete[] data;
        }

        void setCell(T* value, int x, int y, int w, int h) {
            if (w > cellSize || h > cellSize) { LOG("Cell is too big to fit into atlas.", 2); return; }

            for(int ix = 0; ix < cellSize; ix++)
                for(int iy = 0; iy < cellSize; iy++)
                    data[(getWidth() * cellSize * y) + (cellSize * x) + ix + (iy*getWidth())] = (ix >= w || iy >= h) ? 0 : value[iy * w + ix];
        }

    private:
        T* data;

        int cellSize;
        int cellCountX;
        int cellCountY;
    };

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
        static FontAtlas getAtlas(const String& font = "../Hei/Resources/Fonts/xd.ttf");//../Hei/Resources/Fonts/Poppins/Poppins-Black.ttf

    private:
        // Map of fonts containing map of characters
        static UnorderedMap<String, FontAtlas> fonts;
    };

}
