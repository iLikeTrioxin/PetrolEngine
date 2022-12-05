#include <PCH.h>

#include "OpenGLIndexBuffer.h"

namespace PetrolEngine {
	OpenGLIndexBuffer::OpenGLIndexBuffer(const void* data, int64 size) {
		LOG_FUNCTION();

        this->size = size / (int64) sizeof(int);

		glGenBuffers(1, &ID);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::OpenGLIndexBuffer() {
		LOG_FUNCTION();
		
		glGenBuffers(1, &ID);
	}

	void OpenGLIndexBuffer::setData(const void* data, int64 size) {
		LOG_FUNCTION();

		this->size = size / (int64) sizeof(int);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer() { LOG_FUNCTION();
        LOG("Deleting OpenGLIndexBuffer", 1);
		glDeleteBuffers(1, &ID);
	}
}