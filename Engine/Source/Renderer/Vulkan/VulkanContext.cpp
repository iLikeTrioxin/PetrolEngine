#include <PCH.h>

#include "VulkanContext.h"
#include <glad/glad.h>

namespace PetrolEngine {
    int VulkanContext::init(void* loaderProc) {
		return 0;///(loaderProc == nullptr) ? gladLoadGL() : gladLoadGLLoader((GLADloadproc)loaderProc);
	}
}