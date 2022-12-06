#pragma once

#include "Renderer/RendererInterface/VertexArray.h"

namespace PetrolEngine {
	class VulkanVertexArray : public VertexArray {
	public:
		VulkanVertexArray();

		void addVertexBuffer(Ref<VertexBufferApi> vertexBuffer) override;
		void  setIndexBuffer(Ref< IndexBufferApi>  indexBuffer) override;

		~VulkanVertexArray() override;
	};
}