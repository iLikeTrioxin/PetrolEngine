#pragma once

#include "../RendererInterface/UniformBuffer.h"

namespace PetrolEngine{
    class MetalUniformBuffer : public UniformBuffer {
    public:
        MetalUniformBuffer(uint32_t size, uint32_t binding);
        ~MetalUniformBuffer() override;

        void setData(const void* data, uint32_t size, uint32_t offset) override;
    };
}