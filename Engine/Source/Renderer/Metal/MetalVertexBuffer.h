#pragma once

#include "Renderer/RendererInterface/VertexBuffer.h"

namespace PetrolEngine {
	class MetalVertexBuffer : public VertexBuffer {
	public:
		MetalVertexBuffer(VertexLayout layout);
		MetalVertexBuffer(VertexLayout layout, const void* data, int64 size);

		virtual void setData(const void* data, int64 size) override;

		~MetalVertexBuffer() override;
	};
}