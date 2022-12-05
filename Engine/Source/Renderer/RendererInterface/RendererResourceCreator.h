#pragma once

#include <Aliases.h>

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBufferI.h"
#include "VertexArray.h"
#include "RendererI.h"
#include "Shader.h"
#include "Texture.h"
#include "GraphicsContext.h"
#include "Framebuffer.h"
#include "UniformBuffer.h"

#include "Core/Image.h"

namespace PetrolEngine {

    using VL = PetrolEngine::VertexLayout;

    class RendererResourceCreator {
	public:
        virtual VertexBuffer* newVertexBuffer(const VL& layout, const void* data, int64 size) = 0;
		virtual IndexBuffer * newIndexBuffer (const void* data, int64 size) = 0;

        virtual VertexBuffer* newVertexBuffer(const VL& layout) = 0;
        virtual IndexBuffer * newIndexBuffer (                ) = 0;

        virtual UniformBuffer* newUniformBuffer(uint32_t size, uint32_t binding) = 0;

        virtual RendererAPI    * newRenderer       () = 0;
		virtual VertexArray    * newVertexArray    () = 0;
        virtual GraphicsContext* newGraphicsContext() = 0;

        virtual Shader* newShader(const String&          name,
                                  const String&   vertexShader,
                                  const String& fragmentShader,
                                  const String& geometryShader  ) = 0;

        virtual Texture* newTexture(const Image* image) = 0;
        virtual Texture* newTexture(int width, int height, TextureFormat format, TextureType type) = 0;

        virtual Framebuffer* newFramebuffer(const FramebufferSpecification& spec) = 0;
    };

    using RRC = PetrolEngine::RendererResourceCreator;
}