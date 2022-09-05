#include <PCH.h>

#include "VulkanVertexBuffer.h"

namespace PetrolEngine {
	VulkanVertexBuffer::VulkanVertexBuffer(VertexLayout layout, const void* data, int64 size): VertexBufferApi(layout) {
		LOG_FUNCTION();
		
		glGenBuffers(1, &ID);

		glBindBuffer(GL_ARRAY_BUFFER, ID);

		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}

	VulkanVertexBuffer::VulkanVertexBuffer(VertexLayout layout): VertexBufferApi(layout) {
		LOG_FUNCTION();

		glGenBuffers(1, &ID);
	}

	void VulkanVertexBuffer::setData(const void* data, int64 size) {
		LOG_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, ID);

		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}

	VulkanVertexBuffer::~VulkanVertexBuffer() {
		LOG_FUNCTION();
		
		glDeleteBuffers(1, &ID);
	}
}