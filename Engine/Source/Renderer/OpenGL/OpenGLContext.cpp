#include "../../PCH.h"
#include "OpenGLContext.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
namespace Engine {
	int OpenGLContext::init(void* loaderProc) {
		return (loaderProc == nullptr) ? gladLoadGL() : gladLoadGLLoader((GLADloadproc)loaderProc);
	}
}