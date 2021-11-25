#pragma once

#include "../RendererResourceCreator.h"

#include "OpenGLIndexBuffer.h"
#include "OpenGLRenderer.h"
#include "OpenGLShader.h"
#include "OpenGLTexture.h"
#include "OpenGLVertexArray.h"
#include "OpenGLVertexBuffer.h"

namespace PetrolEngine{

    using VL = PetrolEngine::VertexLayout;

    class: public RendererResourceCreator {
        VertexBuffer* newVertexBuffer(const VL& layout, const void* data, int64 size) override { return new OpenGLVertexBuffer(layout, data, size); };
        IndexBuffer * newIndexBuffer (                  const void* data, int64 size) override { return new OpenGLIndexBuffer (        data, size); };
        VertexArray * newVertexArray (                                              ) override { return new OpenGLVertexArray (                  ); };
        Renderer    * newRenderer    (                                              ) override { return new OpenGLRenderer    (                  ); };

        Shader      * newShader      ( String&& vertexShader  ,
                                       String&& fragmentShader,
                                       String&& geometryShader  ) override { return new OpenGLShader(vertexShader.c_str(), fragmentShader.c_str(), geometryShader.c_str()); };

        Texture* newTexture(const Image* image) override { return new OpenGLTexture(image); };
        Texture* newTexture(int width, int height, TextureFormat format) override { return new OpenGLTexture(width, height, format); };
    } OpenGL;
}