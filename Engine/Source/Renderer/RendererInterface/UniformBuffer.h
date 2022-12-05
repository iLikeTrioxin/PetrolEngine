#pragma once

#include <Aliases.h>

namespace PetrolEngine{
    class UniformBuffer {
    public:
        virtual void setData(const void* data, uint32_t size, uint32_t offset) = 0;

        virtual ~UniformBuffer() = default;

        NO_DISCARD int64 getID  () const { return ID  ; }
        NO_DISCARD uint  getSize() const { return size; }
        NO_DISCARD uint  getBinding() const { return binding; }

    protected:
        uint32 binding{};
        int64 size{};
        uint  ID  {};
    };
}