#pragma once

#include "../IndexBuffer.h"

namespace Engine {
    class VulkanIndexBuffer : public IndexBuffer {
	public:
		VulkanIndexBuffer();
		VulkanIndexBuffer(void* data, uint32_t size);

		virtual void setData(void* data, uint32_t size) override;

		~VulkanIndexBuffer();
	};
}