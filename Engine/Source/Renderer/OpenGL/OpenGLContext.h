#pragma once

#include "Renderer/RendererInterface/GraphicsContext.h"

namespace PetrolEngine {
	class OpenGLContext : public GraphicsContext {
	public:
		int init(void* loaderProc) override;
	};
}