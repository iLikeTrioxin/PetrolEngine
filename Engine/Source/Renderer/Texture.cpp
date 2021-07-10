#include "../PCH.h"

#include "Texture.h"
#include "OpenGL/OpenGLTexture.h"
#include <STB/stb_image.h>
#include "Renderer.h"

namespace Engine {
	
	std::shared_ptr<Texture> Texture::create(std::string path, TextureType type, TextureFormat format) {
		switch (RendererAPI::get())
		{
			case RendererAPI::API::None  : return nullptr                                            ; break;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture>(path, type, format); break;
		}
	}
}