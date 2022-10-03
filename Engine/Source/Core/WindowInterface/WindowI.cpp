#include "PCH.h"

#include "WindowI.h"

namespace PetrolEngine {

    float WindowI::getAspectRatio() const {
        return ((float) windowData.width) / ((float)windowData.height);
    }
    
}