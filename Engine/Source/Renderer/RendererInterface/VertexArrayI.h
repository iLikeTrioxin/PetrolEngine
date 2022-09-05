#pragma once

// vertex array takes responsibility for the vertex buffer and the index buffer

// std includes
#include <stdint.h>
#include <string>
#include <vector>

#include "VertexBufferI.h"
#include  "IndexBufferI.h"

namespace PetrolEngine {
	class VertexArrayI {
	public:
		virtual void addVertexBuffer(Ref<VertexBufferI> vertexBuffer) = 0;
		virtual void  setIndexBuffer(Ref<IndexBufferI >  indexBuffer) = 0;

		virtual ~VertexArrayI() = default;

		uint32 getID() { return ID; }

        NO_DISCARD Ref<IndexBufferI> getIndexBuffer() const { return indexBuffer; }

	protected:
		Vector<Ref<VertexBufferI>> vertexBuffers;
		       Ref< IndexBufferI>   indexBuffer;

		uint32 ID;
	};
}