#include "../PCH.h"
#include "Renderer.h"

#include "OpenGL/OpenGLRenderer.h"

#include "../Components.h"
#include "../Core/Window.h"
#include "../DebugTools.h"

namespace Engine {
	std::unique_ptr<RendererAPI> Renderer::rendererAPI;
	
	Renderer Renderer::renderer;
	RendererAPI::API RendererAPI::currentAPI = RendererAPI::API::OpenGL;

	void Renderer::getErrors() {
        GLenum err(glGetError());

        while (err != GL_NO_ERROR) {
            std::string error;
            switch (err) {
            case GL_INVALID_ENUM                 : error = "GL_INVALID_ENUM"                 ; break;
            case GL_INVALID_VALUE                : error = "GL_INVALID_VALUE"                ; break;
            case GL_INVALID_OPERATION            : error = "GL_INVALID_OPERATION"            ; break;
			case GL_STACK_OVERFLOW               : error = "GL_STACK_OVERFLOW"               ; break;
			case GL_STACK_UNDERFLOW              : error = "GL_STACK_UNDERFLOW"              ; break;
            case GL_OUT_OF_MEMORY                : error = "GL_OUT_OF_MEMORY"                ; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: error = "GL_INVALID_FRAMEBUFFER_OPERATION"; break;
			case GL_CONTEXT_LOST                 : error = "GL_CONTEXT_LOST"                 ; break;

            default: error = "Unknown error"; break;
            }
            debug_log("[!] error here:" << error);
            err = glGetError();
        }
	}

	std::unique_ptr<RendererAPI> RendererAPI::create() {
		switch (currentAPI)
		{
		case API::None  : return nullptr;                            break;
		case API::OpenGL: return std::make_unique<OpenGLRenderer>(); break;
		}

		return nullptr;
	}
	
}