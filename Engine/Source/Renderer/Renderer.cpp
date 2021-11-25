#include "Renderer.h"

namespace PetrolEngine{

    Renderer* Renderer::create(RRC* creator) {
        return creator->newRenderer();
    }
}