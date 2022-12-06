#pragma once

#include "Renderer/RendererInterface/IndexBufferI.h"

namespace PetrolEngine {
	class MetalIndexBuffer : public IndexBuffer {
	public:
		MetalIndexBuffer();
		MetalIndexBuffer(const void* data, int64 size);

        void setData(const void* data, int64 size) override;

		~MetalIndexBuffer() override;
	};
}