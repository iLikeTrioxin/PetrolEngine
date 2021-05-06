#pragma once

#include "../GraphicsContext.h"

namespace Engine {
	class OpenGLContext : public GraphicsContext {
	public:
		int init(void* loaderProc) override;
	};
}