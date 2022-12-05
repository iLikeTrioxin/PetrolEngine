#include "Texture.h"

namespace PetrolEngine{
    TextureFormat getFormat(const Image* image){
        uint16 format = 0x0000;

        format ^= image->getComponentsNumber() * 0x1;
        format ^= image->getBitsPerChannel  () * 0x10;
        format ^= image->isHDR              () * 0x1000;

        return static_cast<TextureFormat>(format);
    }
}