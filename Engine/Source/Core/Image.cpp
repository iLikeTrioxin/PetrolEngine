#include <PCH.h>

#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC

#include <stb_image.h>
#include <filesystem>

namespace PetrolEngine {

	Image::Image(const std::string&  path) : Image(path.c_str()) {};

	Image::Image(const char* _path) {
		this->path = std::string(_path);

		data = stbi_load(_path, &width, &height, &componentsNumber, 0);

		if (!data) { LOG("Failed to load image from " + path, 2); return; }

		this->bitsPerChannel = stbi_is_16_bit(_path) ? 16 : 8;
		this->HDR = stbi_is_hdr(_path);

        LOG("Loaded image from " + path, 1);
	}

	Image::~Image() {
		stbi_image_free(data);
	}

	void Image::flipImages(bool flip) {
		stbi_set_flip_vertically_on_load(flip);
	}
}