#pragma once

#include "Renderer/RawRenderer/IndexBufferApi.h"

namespace PetrolEngine {
    class VulkanIndexBuffer : public IndexBufferApi {
	public:
		VulkanIndexBuffer();
		VulkanIndexBuffer(const void* data, int64 size);

		void setData(const void* data, int64 size) override;

		~VulkanIndexBuffer() override;
	};
}