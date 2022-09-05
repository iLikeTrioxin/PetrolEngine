#include "PCH.h"

#include "WindowI.h"

namespace PetrolEngine {

    double deltaXMousePos = 0.0;
    double deltaYMousePos = 0.0;
    double cursorXPos     = 0.0;
    double cursorYPos     = 0.0;
    double deltaTime      = 0.0;

    float WindowI::getAspectRatio() const {
        return ((float) windowData.width) / ((float)windowData.height);
    }
    
}