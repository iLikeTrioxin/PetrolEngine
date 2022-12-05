#pragma once

#include "../RendererInterface/RendererResourceCreator.h"

#include "OpenGLIndexBuffer.h"
#include "OpenGLRenderer.h"
#include "OpenGLShader.h"
#include "OpenGLTexture.h"
#include "OpenGLVertexArray.h"
#include "OpenGLVertexBuffer.h"
#include "OpenGLContext.h"
#include "OpenGLFramebuffer.h"
#include "OpenGLUniformBuffer.h"

namespace PetrolEngine {
    class OPENGL_: public RRC {
    public:
        // with arguments
        VertexBuffer* newVertexBuffer(const VL& layout, const void* data, int64 size) override { return new OpenGLVertexBuffer(layout, data, size); }
        IndexBuffer * newIndexBuffer (                  const void* data, int64 size) override { return new OpenGLIndexBuffer (        data, size); }

        // without arguments
        VertexBuffer* newVertexBuffer(const VL& layout) override { return new OpenGLVertexBuffer(layout); }
        IndexBuffer * newIndexBuffer (                ) override { return new OpenGLIndexBuffer (      ); }

        UniformBuffer* newUniformBuffer(uint32_t size, uint32_t binding) override { return new OpenGLUniformBuffer(size, binding); }

        VertexArray * newVertexArray (                                              ) override { return new OpenGLVertexArray (                  ); }
        RendererAPI  * newRenderer    (                                              ) override { return new OpenGLRenderer    (                  ); }
        GraphicsContext * newGraphicsContext() override { return new OpenGLContext(); }

        Shader* newShader(const String&           name,
                          const String&   vertexShader,
                          const String& fragmentShader,
                          const String& geometryShader  ) override { return new OpenGLShader(name, vertexShader, fragmentShader, geometryShader); }

        Texture* newTexture(const Image* image) override { return new OpenGLTexture(image); }
        Texture* newTexture(int width, int height, TextureFormat format, TextureType type)  override { return new OpenGLTexture(width, height, format, type); }

        Framebuffer* newFramebuffer(const FramebufferSpecification& spec) override { return new OpenGLFramebuffer(spec); }

    };

    extern OPENGL_ OpenGL;
}