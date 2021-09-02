#pragma once

#include "../VertexArray.h"

namespace Engine {
	class VulkanVertexArray : public VertexArray {
	public:
		VulkanVertexArray();

		virtual void addVertexBuffer(std::shared_ptr<VertexBuffer> vertexBuffer) override;
		virtual void  setIndexBuffer(std::shared_ptr< IndexBuffer>  indexBuffer) override;

		~VulkanVertexArray();
	};
}