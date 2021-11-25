#include <PCH.h>

#include "VulkanTexture.h"

namespace PetrolEngine {

	VulkanTexture::VulkanTexture(int width, int height, TextureFormat format) { LOG("Vulkan is not implemented yet.", 4); }
	VulkanTexture::~VulkanTexture() {}

	void VulkanTexture::updateTextureImage(const void * data ) { LOG("Vulkan is not implemented yet.", 4); }
	VulkanTexture::VulkanTexture          (const Image* image) { LOG("Vulkan is not implemented yet.", 4); }
}