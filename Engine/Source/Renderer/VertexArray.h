#pragma once

// std includes
#include <stdint.h>
#include <string>
#include <vector>

#include "VertexBuffer.h"
#include  "IndexBuffer.h"

namespace Engine {
	class VertexArray {
	public:
		
		static std::shared_ptr<VertexArray> create();

		virtual void addVertexBuffer(std::shared_ptr<VertexBuffer> vertexBuffer) = 0;
		virtual void  setIndexBuffer(std::shared_ptr< IndexBuffer>  indexBuffer) = 0;

		virtual ~VertexArray() = default;

		uint32_t getID() { return ID; }

	protected:
		std::vector<std::shared_ptr<VertexBuffer>> vertexBuffers;
		            std::shared_ptr< IndexBuffer>   indexBuffer;

		uint32_t ID;
	};
}