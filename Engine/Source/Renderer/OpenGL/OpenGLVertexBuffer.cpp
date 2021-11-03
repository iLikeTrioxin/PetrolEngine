#include <PCH.h>

#include "OpenGLVertexBuffer.h"

namespace PetrolEngine {
	OpenGLVertexBuffer::OpenGLVertexBuffer(VertexLayout layout, const void* data, int64 size): VertexBuffer(layout) {
		LOG_FUNCTION();
		
		glGenBuffers(1, &ID);

		glBindBuffer(GL_ARRAY_BUFFER, ID);

		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(VertexLayout layout): VertexBuffer(layout) {
		LOG_FUNCTION();

		glGenBuffers(1, &ID);
	}

	void OpenGLVertexBuffer::setData(const void* data, int64 size) {
		LOG_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, ID);

		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer() {
		LOG_FUNCTION();
		
		glDeleteBuffers(1, &ID);
	}
}