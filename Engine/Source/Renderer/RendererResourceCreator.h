#pragma once

#include <Aliases.h>

namespace PetrolEngine {
	
	class VertexBuffer;
	class VertexLayout;
	class IndexBuffer ;
	class VertexArray ;
	class Renderer    ;
	class Shader      ;
    class Texture     ;
    class Image       ;

    enum class TextureType;

	class RendererResourceCreator {
	public:
		virtual VertexBuffer* newVertexBuffer(const VertexLayout& layout, const void* data, int64 size) = 0;
		virtual IndexBuffer * newIndexBuffer (                            const void* data, int64 size) = 0;
		virtual VertexArray * newVertexArray (                                                        ) = 0;
		virtual Renderer    * newRenderer    (                                                        ) = 0;

		virtual Shader      * newShader      ( String&& vertexShader  ,
											   String&& fragmentShader,
			                                   String&& geometryShader  ) = 0;

        virtual Texture* newTexture(const Image* image, TextureType type) = 0;

	};

    using RRC = PetrolEngine::RendererResourceCreator;
}