#pragma once

#include "Renderer/RawRenderer/VertexBufferApi.h"

namespace PetrolEngine {
	class VulkanVertexBuffer : public VertexBufferApi {
	public:
		VulkanVertexBuffer(VertexLayout layout);
		VulkanVertexBuffer(VertexLayout layout, const void* data, int64 size);

        void setData(const void* data, int64 size) override;

		~VulkanVertexBuffer() override;
	};
}