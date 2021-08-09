#pragma once

#include <string>

namespace Engine {

	class Image {
	public:
		Image(const std::string&& path);
		Image(const std::string&  path);
		Image(const char* path);
		
		~Image();

		static void flipImages(bool flip);
		
		unsigned char* getData() { return data; }
		std::string    getPath() { return path; }

		uint8_t getComponentsNumber() { return componentsNumber; }
		uint8_t getBitsPerChannel  () { return bitsPerChannel  ; }
		bool    isHDR              () { return HDR             ; }
		int     getWidth           () { return width           ; }
		int     getHeight          () { return height          ; }

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