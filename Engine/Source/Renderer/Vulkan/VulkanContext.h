#pragma once

#include "../GraphicsContext.h"

namespace Engine {
	class VulkanContext : public GraphicsContext {
	public:
		int init(void* loaderProc) override;
	};
}