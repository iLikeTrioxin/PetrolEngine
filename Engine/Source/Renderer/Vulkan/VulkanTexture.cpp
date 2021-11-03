#include <PCH.h>

#include "VulkanTexture.h"

namespace PetrolEngine {

	VulkanTexture::VulkanTexture(int width, int height, TextureType type, TextureFormat format) {
		this->width  = width;
		this->height = height;
		this->format = format;
		this->type   = type;
	}

	VulkanTexture::~VulkanTexture() { ; }

	void VulkanTexture::updateTextureImage(const void* data) { }

	VulkanTexture::VulkanTexture(const Ref<Image>& image, TextureType type) {
		this->type = type;
		this->id   = 0;
	}
}