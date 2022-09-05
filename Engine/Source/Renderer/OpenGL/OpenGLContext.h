#pragma once

#include "Renderer/RendererInterface/GraphicsContextI.h"

namespace PetrolEngine {
	class OpenGLContext : public GraphicsContextI {
	public:
		int init(void* loaderProc) override;
	};
}