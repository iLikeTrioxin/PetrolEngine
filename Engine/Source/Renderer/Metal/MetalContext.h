#pragma once

#include "Renderer/RendererInterface/GraphicsContext.h"

namespace PetrolEngine {
	class MetalContext : public GraphicsContext {
	public:
		int init(void* loaderProc) override;
	};
}