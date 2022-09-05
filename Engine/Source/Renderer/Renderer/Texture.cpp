#include <PCH.h>

#include "Texture.h"

#include "Renderer.h"

namespace PetrolEngine {

    Ref<TextureI> Texture::create(const Image* image, int a) {
        return Ref<TextureI>(Renderer::getCreator()->newTexture(image, a));
    }

    Ref<TextureI> Texture::create(int width, int height, TextureFormat format) {
        return Ref<TextureI>(Renderer::getCreator()->newTexture(width, height, format));
    }
}