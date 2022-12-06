#pragma once

#include "Renderer/RendererInterface/VertexArray.h"

namespace PetrolEngine {
	class MetalVertexArray : public VertexArray {
	public:
		MetalVertexArray();

		void addVertexBuffer(VertexBuffer*& vertexBuffer) override;
		void  setIndexBuffer(IndexBuffer *&  indexBuffer) override;

		~MetalVertexArray() override;
	};
}