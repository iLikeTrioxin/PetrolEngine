#include <PCH.h>

#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC

#include <stb_image.h>
#include <filesystem>

// TODO: do a safety check if data size is correct in constructor

namespace PetrolEngine {

	Image::Image(const String& path) {
		data = stbi_load(path.c_str(), &width, &height, &componentsNumber, 0);

		if (!data) { LOG("Failed to load image from " + path, 2); return; }

		this->bitsPerChannel = stbi_is_16_bit(path.c_str()) ? 16 : 8;
		this->HDR            = stbi_is_hdr   (path.c_str());

        LOG("Loaded image from " + path, 1);
	}

	Image::Image(const void* data, int width, int height, int bpc, int components, bool hdr) {
		this->componentsNumber = components;
		this->bitsPerChannel   = bpc;
		this->height           = height;
		this->width            = width;
		this->data             = (unsigned char*) data;
		this->HDR              = hdr;
	}

	Image::~Image() {
		stbi_image_free(data);
	}

	void Image::flipImages(bool flip) {
		stbi_set_flip_vertically_on_load(flip);
	}
}