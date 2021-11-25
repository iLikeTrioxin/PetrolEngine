#include <PCH.h>

#include "Texture.h"

namespace PetrolEngine {

    Texture* Texture::create(RRC* creator, int width, int height, TextureFormat format) {
        return creator->newTexture(width, height, format);
    }

    Texture* Texture::create(RRC* creator, const String& path) {
        Image  * image = Image::create(path);
        Texture* texture = creator->newTexture(image);
        delete image;
        return texture;
    }

    Texture* Texture::create(RRC* creator, const Image* image) {
        return creator->newTexture(image);
    }
}