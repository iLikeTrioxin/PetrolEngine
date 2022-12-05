#pragma once

// vertex array takes responsibility for the vertex buffer and the index buffer

// std includes
#include <stdint.h>
#include <string>
#include <vector>

#include "VertexBuffer.h"
#include  "IndexBufferI.h"

namespace PetrolEngine {
	class VertexArray {
	public:
		virtual void  addVertexBuffer(VertexBuffer*& vertexBuffer) = 0;
		virtual void  setIndexBuffer(IndexBuffer *&  indexBuffer) = 0;

		virtual ~VertexArray() = default;

		NO_DISCARD uint32 getID() const { return ID; }
        NO_DISCARD IndexBuffer* getIndexBuffer() const { return indexBuffer; }
        NO_DISCARD const std::vector<VertexBuffer*>& getVertexBuffers() const { return vertexBuffers; }

	protected:
		Vector<VertexBuffer*> vertexBuffers;
		        IndexBuffer*   indexBuffer;

		uint32 ID;
	};
}