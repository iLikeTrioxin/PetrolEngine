#pragma once

#include "../VertexArray.h"

namespace PetrolEngine {
	class VulkanVertexArray : public VertexArray {
	public:
		VulkanVertexArray();

		void addVertexBuffer(Ref<VertexBuffer> vertexBuffer) override;
		void  setIndexBuffer(Ref< IndexBuffer>  indexBuffer) override;

		~VulkanVertexArray() override;
	};
}