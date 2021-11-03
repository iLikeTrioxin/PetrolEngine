#pragma once

#include "../VertexBuffer.h"

namespace PetrolEngine {
	class VulkanVertexBuffer : public VertexBuffer {
	public:
		VulkanVertexBuffer(VertexLayout layout);
		VulkanVertexBuffer(VertexLayout layout, const void* data, int64 size);

        void setData(const void* data, int64 size) override;

		~VulkanVertexBuffer() override;
	};
}