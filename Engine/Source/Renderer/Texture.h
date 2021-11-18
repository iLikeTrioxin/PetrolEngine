#pragma once

#include "../Core/Image.h"
#include "RendererResourceCreator.h"

namespace PetrolEngine {

	enum class TextureType {
		NONE     = 0,
		DIFFUSE  = 1,
		NORMAL   = 2,
		HEIGHT   = 3,
		SPECULAR = 4
	};

	enum class TextureFormat {
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
		RED      = 0x0001,

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


	class Texture {
	public:
		TextureFormat format = TextureFormat::NONE;
		TextureType   type   =   TextureType::NONE;

		virtual ~Texture() = 0;

		virtual void updateTextureImage(const void* data) = 0;

		NO_DISCARD uint getHeight() const { return height; }
		NO_DISCARD uint getWidth () const { return width ; }
		NO_DISCARD uint getID    () const { return id    ; }

        static Texture* create(RRC creator, const Image* image, TextureType type = TextureType::NONE);

        //static Texture* create(const String&     path , TextureType type = TextureType::NONE);
		//static Texture* create(const Image* image, TextureType type = TextureType::NONE);
		//static Texture* create(int width, int height, TextureType type, TextureFormat format);
	protected:
		uint id{};
		uint width  = 0;
		uint height = 0;
	};
}