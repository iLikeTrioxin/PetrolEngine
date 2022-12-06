#pragma once

#include "../RendererInterface/RendererResourceCreator.h"

#include "MetalIndexBuffer.h"
#include "MetalRenderer.h"
#include "MetalShader.h"
#include "MetalTexture.h"
#include "MetalVertexArray.h"
#include "MetalVertexBuffer.h"
#include "MetalContext.h"
#include "MetalFramebuffer.h"
#include "MetalUniformBuffer.h"

namespace PetrolEngine {
    class METAL_: public RRC {
    public:
        // with arguments
        VertexBuffer* newVertexBuffer(const VL& layout, const void* data, int64 size) override { return new MetalVertexBuffer(layout, data, size); }
        IndexBuffer * newIndexBuffer (                  const void* data, int64 size) override { return new MetalIndexBuffer (        data, size); }

        // without arguments
        VertexBuffer* newVertexBuffer(const VL& layout) override { return new MetalVertexBuffer(layout); }
        IndexBuffer * newIndexBuffer (                ) override { return new MetalIndexBuffer (      ); }

        UniformBuffer* newUniformBuffer(uint32_t size, uint32_t binding) override { return new MetalUniformBuffer(size, binding); }

        VertexArray * newVertexArray (                                              ) override { return new MetalVertexArray (                  ); }
        RendererAPI  * newRenderer    (                                              ) override { return new MetalRenderer    (                  ); }
        GraphicsContext * newGraphicsContext() override { return new MetalContext(); }

        Shader* newShader(const String&           name,
                          const String&   vertexShader,
                          const String& fragmentShader,
                          const String& geometryShader  ) override { return new MetalShader(name, vertexShader, fragmentShader, geometryShader); }

        Texture* newTexture(const Image* image) override { return new MetalTexture(image); }
        Texture* newTexture(int width, int height, TextureFormat format, TextureType type)  override { return new MetalTexture(width, height, format, type); }

        Framebuffer* newFramebuffer(const FramebufferSpecification& spec) override { return new MetalFramebuffer(spec); }

    };

    extern METAL_ Metal;
}