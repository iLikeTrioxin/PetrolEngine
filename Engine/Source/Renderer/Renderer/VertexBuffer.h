#pragma once

#include "Renderer.h"

namespace PetrolEngine {
    class VertexBuffer {
    public:
        static Ref<VertexBufferI> create(VertexLayout layout) {
            return Ref<VertexBufferI>(Renderer::getCreator()->newVertexBuffer(layout));
        }
        static Ref<VertexBufferI> create(VertexLayout layout, const void* data, int64 size) {
            return Ref<VertexBufferI>(Renderer::getCreator()->newVertexBuffer(layout, data, size));
        }
    };
}