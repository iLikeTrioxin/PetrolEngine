#pragma once

#include <Aliases.h>

#include "VertexBufferI.h"
#include "VertexArrayI.h"
#include "IndexBufferI.h"
#include "VertexArrayI.h"
#include "RendererI.h"
#include "ShaderI.h"
#include "TextureI.h"
#include "GraphicsContextI.h"
#include "FramebufferI.h"

#include "Core/Image.h"

namespace PetrolEngine {

    using VL = PetrolEngine::VertexLayout;

    class RendererResourceCreator {
	public:
        virtual VertexBufferI* newVertexBuffer(const VL& layout, const void* data, int64 size) = 0;
		virtual IndexBufferI * newIndexBuffer (const void* data, int64 size) = 0;

        virtual VertexBufferI* newVertexBuffer(const VL& layout) = 0;
        virtual IndexBufferI * newIndexBuffer (                ) = 0;

		virtual VertexArrayI * newVertexArray (                                              ) = 0;
		virtual RendererI    * newRenderer    (                                              ) = 0;
        virtual GraphicsContextI* newGraphicsContext() = 0;

        virtual ShaderI* newShader(const char* vertexShader  ,
								   const char* fragmentShader,
								   const char* geometryShader  ) = 0;

        virtual TextureI* newTexture(const Image* image, int a= 0x1401) = 0;
        virtual TextureI* newTexture(int width, int height, TextureFormat format) = 0;

        virtual FramebufferI* newFramebuffer(const FramebufferSpecification& spec) = 0;
    };

    using RRC = PetrolEngine::RendererResourceCreator;
}