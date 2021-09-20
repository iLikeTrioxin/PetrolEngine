#include <PCH.h>

#include "VulkanIndexBuffer.h"

namespace PetrolEngine {

    /*
    OpenGLIndexBuffer::OpenGLIndexBuffer(void* data, uint32_t size) {
		LOG_FUNCTION();
		
		this->size = size / sizeof(int);
		
		glGenBuffers(1, &ID);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::OpenGLIndexBuffer() {
		LOG_FUNCTION();
		
		glGenBuffers(1, &ID);
	}

	void OpenGLIndexBuffer::setData(void* data, uint32_t size) {
		LOG_FUNCTION();

		this->size = size / sizeof(int);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer() {
		LOG_FUNCTION();
		
		glDeleteBuffers(1, &ID);
	}
     */
}