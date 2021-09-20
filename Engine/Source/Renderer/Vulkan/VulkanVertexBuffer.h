#pragma once

#include "../VertexBuffer.h"

namespace PetrolEngine {
	class VulkanVertexBuffer : public VertexBuffer {
	public:
		VulkanVertexBuffer(VertexLayout layout);
		VulkanVertexBuffer(VertexLayout layout, void* data, uint32_t size);

		virtual void setData(void* data, uint32_t size) override;

		~VulkanVertexBuffer();
	};
}