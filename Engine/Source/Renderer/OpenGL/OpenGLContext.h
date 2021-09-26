#pragma once

#include "../GraphicsContext.h"

namespace PetrolEngine {
	class OpenGLContext : public GraphicsContext {
	public:
        OpenGLContext(void* window) {this->window = window;}

		int init(void* loaderProc) override;
	};
}