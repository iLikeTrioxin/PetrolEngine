#pragma once

#include "../GraphicsContext.h"

namespace PetrolEngine {
	class VulkanContext : public GraphicsContext {
	public:
		int init(void* loaderProc) override;
	};
}