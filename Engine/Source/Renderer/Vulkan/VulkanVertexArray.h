#pragma once

#include "Renderer/RawRenderer/VertexArrayApi.h"

namespace PetrolEngine {
	class VulkanVertexArray : public VertexArrayApi {
	public:
		VulkanVertexArray();

		void addVertexBuffer(Ref<VertexBufferApi> vertexBuffer) override;
		void  setIndexBuffer(Ref< IndexBufferApi>  indexBuffer) override;

		~VulkanVertexArray() override;
	};
}