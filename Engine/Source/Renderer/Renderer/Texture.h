#pragma once

#include "../../Core/Image.h"

#include "Renderer/RendererInterface/TextureI.h"

namespace PetrolEngine {
    class Texture {
    public:
        static Ref<TextureI> create(const Image* image,int a= 0x1401);
        static Ref<TextureI> create(int width, int height, TextureFormat format);
    };
}