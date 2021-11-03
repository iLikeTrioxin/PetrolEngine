#pragma once

// std includes
#include <stdint.h>
#include <string>
#include <vector>

#include "VertexBuffer.h"
#include  "IndexBuffer.h"

namespace PetrolEngine {
	class VertexArray {
	public:
		
		static Ref<VertexArray> create();

		virtual void addVertexBuffer(Ref<VertexBuffer> vertexBuffer) = 0;
		virtual void  setIndexBuffer(Ref< IndexBuffer>  indexBuffer) = 0;

		virtual ~VertexArray() = default;

		uint32_t getID() { return ID; }

	protected:
		std::vector<Ref<VertexBuffer>> vertexBuffers;
		            Ref< IndexBuffer>   indexBuffer;

		uint32_t ID;
	};
}