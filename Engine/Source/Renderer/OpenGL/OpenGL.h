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

namespace PetrolEngine {
    class OPENGL_: public RRC {
    public:
        // with arguments
        VertexBufferI* newVertexBuffer(const VL& layout, const void* data, int64 size) override { return new OpenGLVertexBuffer(layout, data, size); }
        IndexBufferI * newIndexBuffer (                  const void* data, int64 size) override { return new OpenGLIndexBuffer (        data, size); }

        // without arguments
        VertexBufferI* newVertexBuffer(const VL& layout) override { return new OpenGLVertexBuffer(layout); }
        IndexBufferI * newIndexBuffer (                ) override { return new OpenGLIndexBuffer (      ); }


        VertexArrayI * newVertexArray (                                              ) override { return new OpenGLVertexArray (                  ); }
        RendererI    * newRenderer    (                                              ) override { return new OpenGLRenderer    (                  ); }
        GraphicsContextI * newGraphicsContext() override { return new OpenGLContext(); }

        ShaderI* newShader(const char* vertexShader  ,
                           const char* fragmentShader,
                           const char* geometryShader  ) override { return new OpenGLShader(vertexShader, fragmentShader, geometryShader); }

        TextureI* newTexture(const Image* image,int a= GL_UNSIGNED_BYTE) { return new OpenGLTexture(image, a); }
        TextureI* newTexture(int width, int height, TextureFormat format) { return new OpenGLTexture(width, height, format); }

        FramebufferI* newFramebuffer(const FramebufferSpecification& spec) override { return new OpenGLFramebuffer(spec); }

    } OpenGL;
}