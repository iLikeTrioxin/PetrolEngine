#pragma once

namespace PetrolEngine {
    class GraphicsContextI {
    public:
        virtual ~GraphicsContextI() = default;

        virtual int init(void* loaderProc = nullptr) = 0;
    };
}