#include <PCH.h>

#include "MetalVertexBuffer.h"

namespace PetrolEngine {
	MetalVertexBuffer::MetalVertexBuffer(VertexLayout layout, const void* data, int64 size): VertexBuffer(layout) {
		LOG_FUNCTION();
	}

	MetalVertexBuffer::MetalVertexBuffer(VertexLayout layout): VertexBuffer(layout) {
		LOG_FUNCTION();
	}

	void MetalVertexBuffer::setData(const void* data, int64 size) {
		LOG_FUNCTION();
	}

	MetalVertexBuffer::~MetalVertexBuffer() {
        LOG_FUNCTION();
	}
}