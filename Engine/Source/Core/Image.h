#pragma once

#include <string>
#include <Aliases.h>

namespace PetrolEngine {

	class Image {
	public:
        static Image* create(const String& path) { return new Image(path); }
        static Image* create(int width, int height, TextureType type, TextureFormat format) { return new Image(path); }

		~Image();

		static void flipImages(bool flip);
		
		NO_DISCARD unsigned char* getData() const { return data; }

		NO_DISCARD uint8 getComponentsNumber() const { return componentsNumber; }
		NO_DISCARD uint8 getBitsPerChannel  () const { return bitsPerChannel  ; }
		NO_DISCARD bool  isHDR              () const { return HDR             ; }
		NO_DISCARD int   getWidth           () const { return width           ; }
		NO_DISCARD int   getHeight          () const { return height          ; }

    public:
        explicit Image(const String&  path);
        explicit Image(int width, int height, TextureType type, TextureFormat format);

    private:
		int  width  = 0;
		int  height = 0;
		bool HDR    = false;

		int componentsNumber = 0;
		int bitsPerChannel   = 0;

		unsigned char* data = nullptr;
	};
}