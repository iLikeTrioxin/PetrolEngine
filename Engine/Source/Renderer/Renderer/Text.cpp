#include <PCH.h>

#include "Text.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include <iostream>

#include "Renderer/Renderer/Texture.h"

String getFontPath(const String& font) {
    if (font.rfind(".ttf") != String::npos) return font;

    #ifdef _WIN32
    return "C:/Windows/Fonts/" + font + ".ttf";
    #endif

    #ifdef __linux__
    return "/usr/share/fonts/TTF/" + font + ".ttf";
    #endif

    return "";
}

namespace PetrolEngine {
    static FT_Library lib;
    UnorderedMap<String, Text::FontAtlas> Text::fonts;

    Text::FontAtlas Text::getAtlas(const String& character) {
        if(fonts.find(character) == fonts.end())
            loadFont(character);

        return Text::fonts[character];
    }

    int Text::destroy() {
        for(auto& font : fonts)
            delete font.second.atlas;

        fonts.clear();

        return FT_Done_FreeType(lib);
    }

    int Text::init() {
        FT_Error err = FT_Init_FreeType(&lib);

        if(err)
            LOG("Couldn't initialize FreeType Library (error code:" + toString(err) + ")", 3);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        //glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

        return err;
    }

    int Text::loadFont(const String& font) {
        FT_Face face;
        FT_Error err = 0;

        auto* atlas = new Atlas<unsigned char>(96, 12, 12);

        String fontPath = getFontPath(font);
        LOG(fontPath, 1);

        err =  err ? err : FT_New_Face(lib, fontPath.c_str(), 0, &face);
        err =  err ? err : FT_Set_Pixel_Sizes(face, 0, 64);

        if(err) { LOG("Failed to load font (error code:" + toString(err) + ")", 2); return err; }
        FT_GlyphSlot slot = face->glyph;

        UnorderedMap<unsigned char, AtlasCharacter> characters;
        characters.reserve(128);
        for(unsigned char asciiCode = 0; asciiCode < 128; asciiCode++) {
            err = err ? err : FT_Load_Char(face, asciiCode, FT_LOAD_RENDER);
             err = err ? err : FT_Render_Glyph(slot, FT_RENDER_MODE_SDF);

            if(face->glyph->bitmap.width * face->glyph->bitmap.rows == 0) continue;

            if(err) { LOG("FREETYPE ERROR: Failed to load glyph with ASCII " + toString(asciiCode) + " (error code:" + toString(err) + ")", 2); continue; }

            uint8 column = asciiCode % atlas->getCellCountX();
            uint8 row    = asciiCode / atlas->getCellCountX();

            atlas->setCell(
                slot->bitmap.buffer,
                column,
                row,
                slot->bitmap.width,
                slot->bitmap.rows
            );

            // now store character for later use
            characters[asciiCode] = AtlasCharacter {
                    glm::vec4(
                        (float) (column * atlas->getCellSize()) / (float) atlas->getWidth (),
                        (float) (row    * atlas->getCellSize()) / (float) atlas->getHeight(),
                        (float) (column * atlas->getCellSize() + face->glyph->bitmap.width) / (float) atlas->getWidth (),
                        (float) (row    * atlas->getCellSize() + face->glyph->bitmap.rows ) / (float) atlas->getHeight()
                    ),
                    glm::vec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                    glm::vec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                    (long) (face->glyph->advance.x * 1.3)
            };
        }

        fonts[font] = FontAtlas {
            atlas,
            characters
        };

        FT_Done_Face(face);
        return 0;
    }

}
