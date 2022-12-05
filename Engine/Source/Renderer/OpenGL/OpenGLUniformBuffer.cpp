#include <PCH.h>

#include "OpenGLUniformBuffer.h"

namespace PetrolEngine{
    OpenGLUniformBuffer::OpenGLUniformBuffer(uint32_t size, uint32_t binding) {
        this->size = size;
        this->binding = binding;

        glCreateBuffers(1, &this->ID);
        glNamedBufferData(this->ID, size, nullptr, GL_DYNAMIC_DRAW); // TODO: investigate usage hint
        glBindBufferBase(GL_UNIFORM_BUFFER, binding, this->ID);
    }

    OpenGLUniformBuffer::~OpenGLUniformBuffer() {
        glDeleteBuffers(1, &this->ID);
    }


    void OpenGLUniformBuffer::setData(const void* data, uint32_t size, uint32_t offset) {
        glNamedBufferSubData(this->ID, offset, size, data);
    }
}