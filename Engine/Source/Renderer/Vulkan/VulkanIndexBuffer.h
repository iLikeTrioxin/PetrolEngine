#pragma once

#include "../IndexBuffer.h"

namespace PetrolEngine {
    class VulkanIndexBuffer : public IndexBuffer {
	public:
		VulkanIndexBuffer();
		VulkanIndexBuffer(void* data, uint32_t size);

		void setData(void* data, uint32_t size) override;

		~VulkanIndexBuffer() override;
	};
}