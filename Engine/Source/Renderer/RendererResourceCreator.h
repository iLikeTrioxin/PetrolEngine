#pragma once

#include <Aliases.h>

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"

#include "../Core/Image.h"

namespace PetrolEngine {

    class RendererResourceCreator {
	public:
		virtual VertexBuffer* newVertexBuffer(const VertexLayout& layout, const void* data, int64 size) = 0;
		virtual IndexBuffer * newIndexBuffer (                            const void* data, int64 size) = 0;
		virtual VertexArray * newVertexArray (                                                        ) = 0;
		virtual Renderer    * newRenderer    (                                                        ) = 0;

        virtual Shader* newShader( String&& vertexShader  ,
                                   String&& fragmentShader,
                                   String&& geometryShader  ) = 0;

        virtual Texture* newTexture(const Image* image) = 0;
        virtual Texture* newTexture(int width, int height, TextureFormat format) = 0;
    };

    using RRC = PetrolEngine::RendererResourceCreator;
}