#pragma once

#include "../RendererInterface/UniformBuffer.h"

namespace PetrolEngine{
    class OpenGLUniformBuffer : public UniformBuffer {
    public:
        OpenGLUniformBuffer(uint32_t size, uint32_t binding);
        ~OpenGLUniformBuffer() override;

        void setData(const void* data, uint32_t size, uint32_t offset) override;
    };
}