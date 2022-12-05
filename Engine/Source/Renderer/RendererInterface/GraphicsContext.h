#pragma once

namespace PetrolEngine {
    class GraphicsContext {
    public:
        virtual ~GraphicsContext() = default;

        virtual int init(void* loaderProc = nullptr) = 0;
    };
}