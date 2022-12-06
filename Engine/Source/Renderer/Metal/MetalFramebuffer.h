#pragma once

#include <Aliases.h>

#include "../RendererInterface/Framebuffer.h"

namespace PetrolEngine{

    class MetalFramebuffer : public Framebuffer{
    public:
        MetalFramebuffer(const FramebufferSpecification& spec);

        void addAttachment(Texture*& texture) override;

        ~MetalFramebuffer() override;

    };

}