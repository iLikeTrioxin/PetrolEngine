#include <PCH.h>

#include "GraphicsContext.h"
#include <memory>
#include "Renderer.h"
#include "OpenGL/OpenGLContext.h"

namespace PetrolEngine {
	std::unique_ptr<GraphicsContext> GraphicsContext::create(void* window) {

	    return std::make_unique<OpenGLContext>();
	}
}