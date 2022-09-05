#include <PCH.h>

#include "OpenGLFramebuffer.h"

namespace PetrolEngine{

        OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecification& spec) {
            glGenFramebuffers(1, &id);
            glBindFramebuffer(GL_FRAMEBUFFER, id);

            glGenTextures(1, &tid);
            glBindTexture(GL_TEXTURE_2D, tid);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, spec.width, spec.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tid, 0);

            glGenTextures(1, &did);
            glBindTexture(GL_TEXTURE_2D, did);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, spec.width, spec.height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);

            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, did, 0);

            if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
                LOG("Framebuffer is not complete!", 2);

            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        OpenGLFramebuffer::~OpenGLFramebuffer() {
            glDeleteFramebuffers(1, &id);
        }

        void OpenGLFramebuffer::addAttachment(Ref<TextureI> texture) {
            attachments.push_back(texture);

            glBindFramebuffer(GL_FRAMEBUFFER, id);
            glBindTexture(GL_TEXTURE_2D, texture->getID());

            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture->getID(), 0);

            if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
                LOG("Framebuffer is not complete!", 2);

            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

}