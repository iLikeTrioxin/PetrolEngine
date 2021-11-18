#include <PCH.h>

#include "Text.h"
#include <iostream>
#include <ft2build.h>

#include "Texture.h"
#include FT_FREETYPE_H

namespace PetrolEngine {
	UnorderedMap<char, Text::Character> Text::characters;

    Text::Character Text::get(char character) {
        return characters[character];
    }

	void Text::init(const String& fontPath) {
        FT_Library ft;

        if (FT_Error error = FT_Init_FreeType(&ft)) {
            LOG("FREETYPE ERROR: Could not init FreeType Library (error code:" + std::to_string(error) + ")", 3);
            return;
        }

        FT_Face face;
        if (FT_Error error = FT_New_Face(ft, fontPath.c_str(), 0, &face)) {
            LOG("FREETYPE ERROR: Failed to load font (error code:" + std::to_string(error) + ")", 2);
            return;
        }

        FT_Set_Pixel_Sizes(face, 0, 32);
        
        FT_Vector pen   { 0, 0 };
        FT_Matrix matrix{
            0x10000L, 0x00001L,
            0x00001L, 0x10000L
        };

        for (unsigned char c = 0; c < 128; c++)
        {
            /* set transformation */
            FT_Set_Transform(face, &matrix, &pen);

            // load character glyph 
            if (FT_Error error = FT_Load_Char(face, c, FT_LOAD_RENDER)) {
                LOG("FREETYPE ERROR: Failed to load Glyph with ASCII ID " + std::to_string(c) + " (error code:" + std::to_string(error) + ")", 2);
                continue;
            }

            auto texture = Texture::create(
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                TextureType  ::NONE,
                TextureFormat::RED
            );

            texture->updateTextureImage(face->glyph->bitmap.buffer);

            // now store character for later use
            Character character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                face->glyph->advance.x
            };

            characters[c] = character;
        }

        FT_Done_Face(face);
        FT_Done_FreeType(ft);
	}

}