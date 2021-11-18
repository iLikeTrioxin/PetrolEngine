#include <PCH.h>

#include "IndexBuffer.h"

namespace PetrolEngine {
	IndexBuffer* IndexBuffer::create(RRC creator, const void* data, int64 size) {
		return creator.newIndexBuffer(data, size);
	}
}