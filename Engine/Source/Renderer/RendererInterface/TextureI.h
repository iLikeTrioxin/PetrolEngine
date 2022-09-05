#pragma once

#include "Aliases.h"

#include "Core/Image.h"

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

    TextureFormat getFormat(const Image* image);

	class TextureI {
	public:
		virtual ~TextureI() = default;

		virtual void updateTextureImage(const void* data) = 0;

		NO_DISCARD uint getHeight() const { return height; }
		NO_DISCARD uint getWidth () const { return width ; }
		NO_DISCARD uint getID    () const { return id    ; }

        // static TextureI* create(RRC* creator, const Image * image);
        // static TextureI* create(RRC* creator, const String& path );

        // static TextureI* create(RRC* creator, int width, int height, TextureFormat format);

	public:
		TextureFormat format = TextureFormat::NONE;

		uint id;
		uint width  = 0;
		uint height = 0;
	};
}
