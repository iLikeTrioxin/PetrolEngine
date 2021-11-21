#include <PCH.h>

#include "Texture.h"

namespace PetrolEngine {

    Texture* Texture::create(RRC creator, int width, int height, TextureType type, TextureFormat format) {
        return creator.newTexture(width, height, type, format);
    }

    Texture* Texture::create(RRC creator, const String& path , TextureType type) {
        return creator.newTexture(move(Image::create(path)), type);
    }

    Texture* Texture::create(RRC creator, const Image* image, TextureType type) {
        return creator.newTexture(image, type);
    }
}