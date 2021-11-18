#include <PCH.h>

#include "VertexBuffer.h"

namespace PetrolEngine {

    VertexBuffer* VertexBuffer::create(RRC creator, const VertexLayout& layout, const void* data, int64 size) {
		return creator.newVertexBuffer(layout, data, size);
	}
}