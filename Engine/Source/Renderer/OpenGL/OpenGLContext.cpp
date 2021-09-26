#include <PCH.h>

#include "OpenGLContext.h"

#include <glad/glad.h>

namespace PetrolEngine {
	int OpenGLContext::init(void* loaderProc) {
		return (loaderProc == nullptr) ? gladLoadGL() : gladLoadGLLoader((GLADloadproc)loaderProc);
	}
}