#pragma once

#include <Aliases.h>
#include "Renderer/RendererInterface/VertexArray.h"
#include "Renderer/RendererInterface/Shader.h"

namespace PetrolEngine {
    class VertexAttribute {
    public:
        const uint8 typeBytes; uint8 const * p;
        VertexAttribute(const uint8 typeBytes, uint8 const * p) : typeBytes(typeBytes), p(p) {}
        template<typename T>
        void operator=(T t) const {
//            if (sizeof(T) != typeBytes) throw std::runtime_error("Type size mismatch");
            *( (T*)p ) = t;
        }
    };

    class VertexF {
    public:
        const VertexLayout* layout; uint8 const * p;

        VertexF(const VertexLayout* layout, uint8 const * p) : layout(layout), p(p) {}

        auto operator[](const char* name) const {
            uint8 const * tmp = p;

            for (auto& element : layout->getElements()) {
                uint8 size = ShaderDataTypeSize(element.type);

                if (element.name == name)
                    return VertexAttribute(size, tmp);

                tmp += size;
            }
        }
    };

    class VertexData{
    public:
        VertexLayout layout;
        uint64 elementSize  = 0; // in bytes
        uint64 elementCount = 0;
        uint64 reserved     = 0;
        uint8* data         = 0;

        VertexData() = default;

        void changeLayout(VertexLayout layout){
            this->layout = layout;

            for(auto& element : layout.getElements())
                this->elementSize += ShaderDataTypeSize(element.type);
        }

        ~VertexData(){
            delete[] data;
        }

        void resize(uint64 count){
            if(count <= reserved) return;

            uint8* tmp = data;

            data = (uint8*) malloc(count * elementSize);

            if(tmp != nullptr) *data = *tmp;

            reserved = count;

            delete[] tmp;
        }

        VertexF operator[](int i){
            return {&layout, data + (i * elementSize)};
        }
    };
}