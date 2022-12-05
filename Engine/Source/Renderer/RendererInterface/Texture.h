#pragma once

#include "Aliases.h"

#include "Core/Image.h"
#include "../../Atlas.h"
#include <glm/vec2.hpp>

namespace PetrolEngine {

	enum class TextureFormat: uint16 {
		NONE = 0x0000,
		
		// Structure:
		// C - type ( 1 - R, 2 - RG, 3 - RGB, 4 - RGBA, 5 - DEPTH)
		// B - bits per channel
		// A - type ( 0 - normal, 1 - float, 2 - int, 3 - uint)
		// 
		//   A B  C
		//   | |  |
		// 0x0 00 0
		// 
		// 
		
		// color formats
		RED      = 0x0081,

		RGBA16UI = 0x3104,
		RGBA8UI  = 0x3084,

		RGBA16F  = 0x1104,
		RGBA32F  = 0x1204,

		RGBA8    = 0x0084,
		RGBA16   = 0x0104,

		RGB8     = 0x0083,
		RGB8UI   = 0x3083,
		RGB16    = 0x0103,
		RGB16UI  = 0x3103,

		RG8      = 0x0082,
		RG8UI    = 0x3082,
		RG16     = 0x0102,
		RG16UI   = 0x3102,

		// Depth formats
		DEPTH16  = 0x0085,
		DEPTH24  = 0x0185,
		DEPTH32  = 0x0205,
		DEPTH32F = 0x1205
	};

    enum class TextureType: uint16{
        Texture2D = 0x0002,
        Texture3D = 0x0003,
        TextureCube = 0x0004
    };

    TextureFormat getFormat(const Image* image);

	class Texture {
	public:
		virtual ~Texture() = default;

		virtual void updateTextureImage(const void* data, int index = 0) = 0;
        void hejka(const String& path){
            Image* image = Image::create(path);

            if(type == TextureType::TextureCube){
                int width = image->getWidth();
                int height = image->getHeight();
                int size = width / 4;

                this->width = size;
                this->height = size;

                Atlas<uint32> atlas(size, width/size, height/size, image->getData(), image->getComponentsNumber() * image->getBitsPerChannel() * image->getWidth() * image->getHeight() / 8);

                const glm::ivec2 coords[6] = {
                        {2, 1}, // right
                        {0, 1}, // left
                        {1, 0}, // top
                        {1, 2}, // bottom
                        {1, 1}, // front
                        {3, 1}  // back
                };

                for(int i = 0; i < 6; i++){
                    uint32* face = atlas.getCell(coords[i].x, coords[i].y, false, true);
                    int j = i;

                    if(i == 2) j = 3;
                    if(i == 3) j = 2;

                    updateTextureImage(face, j);
                    delete[] face;
                }
            }

            if(type == TextureType::Texture2D){
                updateTextureImage(image->getData());
            }

            delete image;
        }

		NO_DISCARD uint getHeight() const { return height; }
		NO_DISCARD uint getWidth () const { return width ; }
		NO_DISCARD uint getID    () const { return id    ; }

        // static TextureI* create(RRC* creator, const Image * image);
        // static TextureI* create(RRC* creator, const String& path );

        // static TextureI* create(RRC* creator, int width, int height, TextureFormat format);

	public:
		TextureFormat format = TextureFormat::NONE;
        TextureType   type   = TextureType  ::Texture2D;

		uint id     = 0;
		uint width  = 0;
		uint height = 0;
	};
}
