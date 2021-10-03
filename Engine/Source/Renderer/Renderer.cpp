#include <PCH.h>
#include "Renderer.h"
#include <iostream>
#include "OpenGL/OpenGLRenderer.h"

#include "../Components.h"
#include "../Core/Window.h"
#include "../DebugTools.h"

namespace PetrolEngine {
	    Renderer     Renderer::renderer;
	Ptr<RendererAPI> Renderer::rendererAPI;

	struct Renderer2DData{

	    uint32_t maxTextures = 32;
	    Vector<unsigned int> textures;
	};

	Renderer2DData renderer2DData;

	void Renderer::renderText(const String& text, Transform& transform) { LOG_FUNCTION();
	    rendererAPI->renderText(text, transform);
	}

	void Renderer::init(RendererAPI::API  targetAPI, bool debug){
	    rendererAPI = RendererAPI::create(targetAPI);

	    rendererAPI->init(debug);
	    //RendererAPI::getInstance()->getDeviceConstantValue(DeviceConstant::MAX_TEXTURE_IMAGE_UNITS, &renderer2DData.maxTextures);

	    //DEBUG_LOG("[*] Textures: " + std::to_string(renderer2DData.maxTextures));
	}

	void Renderer::renderMesh(Mesh& m, Transform& t, Camera& c) { LOG_FUNCTION();
	    rendererAPI->renderMesh(m, t, c);
	}

	void Renderer::clear() { LOG_FUNCTION();
	    rendererAPI->clear();
	}

	void Renderer::OnWindowResize(uint32_t w, uint32_t h) { LOG_FUNCTION();
	    rendererAPI->setViewport(0, 0, w, h);
	}

	void Renderer::getDeviceConstantValue(DeviceConstant d, void* o) { LOG_FUNCTION();
	    rendererAPI->getDeviceConstantValue(d, o);
	}


	void Renderer::getErrors() {
	    GLenum err;
        while ( (err = glGetError()) != GL_NO_ERROR) {
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
            DEBUG_LOG("[!] error here:" << error);
            err = glGetError();
        }
	}
}