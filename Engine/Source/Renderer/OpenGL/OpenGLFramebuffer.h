#pragma once

#include <Aliases.h>

#include "../RendererInterface/FramebufferI.h"

namespace PetrolEngine{

    class OpenGLFramebuffer : public FramebufferI{
    public:
        OpenGLFramebuffer(const FramebufferSpecification& spec);

        virtual void addAttachment(Ref<TextureI> texture) override;

        ~OpenGLFramebuffer() override;

    };

}