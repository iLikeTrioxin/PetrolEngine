#pragma once

#include "../VertexArray.h"

namespace PetrolEngine {
	class VulkanVertexArray : public VertexArray {
	public:
		VulkanVertexArray();

		void addVertexBuffer(std::shared_ptr<VertexBuffer> vertexBuffer) override;
		void  setIndexBuffer(std::shared_ptr< IndexBuffer>  indexBuffer) override;

		~VulkanVertexArray();
	};
}