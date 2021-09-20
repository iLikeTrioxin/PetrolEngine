#pragma once

#include <string>

namespace PetrolEngine {

	class Image {
	public:
		Image(const std::string&& path);
		Image(const std::string&  path);
		Image(const char* path);
		
		~Image();

		static void flipImages(bool flip);
		
		unsigned char* getData() const { return data; }
		std::string    getPath() const { return path; }

		uint8_t getComponentsNumber() const { return componentsNumber; }
		uint8_t getBitsPerChannel  () const { return bitsPerChannel  ; }
		bool    isHDR              () const { return HDR             ; }
		int     getWidth           () const { return width           ; }
		int     getHeight          () const { return height          ; }

	private:
		std::string path;

		int width;
		int height;
		bool HDR;
		uint8_t componentsNumber;
		uint8_t bitsPerChannel;

		unsigned char* data;
	};
}