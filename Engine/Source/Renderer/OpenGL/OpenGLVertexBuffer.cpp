#include <PCH.h>

#include "OpenGLVertexBuffer.h"

namespace Engine {
	OpenGLVertexBuffer::OpenGLVertexBuffer(VertexLayout layout, void* data, uint32_t size): VertexBuffer(layout) {
		LOG_FUNCTION();
		
		glGenBuffers(1, &ID);

		glBindBuffer(GL_ARRAY_BUFFER, ID);

		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(VertexLayout layout): VertexBuffer(layout) {
		LOG_FUNCTION();

		glGenBuffers(1, &ID);
	}

	void OpenGLVertexBuffer::setData(void* data, uint32_t size) {
		LOG_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, ID);

		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer() {
		LOG_FUNCTION();
		
		glDeleteBuffers(1, &ID);
	}
}