#pragma once

#include "../IndexBuffer.h"

namespace PetrolEngine {
    class VulkanIndexBuffer : public IndexBuffer {
	public:
		VulkanIndexBuffer();
		VulkanIndexBuffer(const void* data, int64 size);

		void setData(const void* data, int64 size) override;

		~VulkanIndexBuffer() override;
	};
}