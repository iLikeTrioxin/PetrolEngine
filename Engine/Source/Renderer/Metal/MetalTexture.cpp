#include <PCH.h>

#include "MetalTexture.h"
#include "../../Atlas.h"
#include "../../Core/Image.h"

namespace PetrolEngine {

	MetalTexture::MetalTexture(int width, int height, TextureFormat format, TextureType type) {

	}

	MetalTexture::~MetalTexture() {
	}

	void MetalTexture::updateTextureImage(const void* data, int index = -1) {
	}

	MetalTexture::MetalTexture(const Image* image) {
	}
}