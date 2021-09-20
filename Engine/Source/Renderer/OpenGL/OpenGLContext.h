#pragma once

#include "../GraphicsContext.h"

namespace PetrolEngine {
	class OpenGLContext : public GraphicsContext {
	public:
		int init(void* loaderProc) override;
	};
}