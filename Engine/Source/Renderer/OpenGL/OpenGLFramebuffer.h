#pragma once

#include <Aliases.h>

#include "../RendererInterface/Framebuffer.h"

namespace PetrolEngine{

    class OpenGLFramebuffer : public Framebuffer{
    public:
        OpenGLFramebuffer(const FramebufferSpecification& spec);

        void addAttachment(Texture*& texture) override;

        ~OpenGLFramebuffer() override;

    };

}