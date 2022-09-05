#pragma once

#include <memory>
#include "../RendererInterface/GraphicsContextI.h"
#include "Renderer.h"

namespace PetrolEngine {
    class GraphicsContext {
    public:
        static Ref<GraphicsContextI> create(){
            return Ref<GraphicsContextI>(Renderer::getCreator()->newGraphicsContext());
        }
    };
}