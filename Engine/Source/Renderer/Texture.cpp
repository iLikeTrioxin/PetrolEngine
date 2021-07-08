#include "../PCH.h"

#define STB_IMAGE_IMPLEMENTATION

#include "Texture.h"
#include "OpenGL/OpenGLTexture.h"
#include <STB/stb_image.h>
#include "Renderer.h"

namespace Engine {

	void initalizeTextureSettings(bool flipImage) {
		stbi_set_flip_vertically_on_load(flipImage);
	}

	std::shared_ptr<Texture> Texture::create(std::string path, TextureType type, TextureFormat format) {
		switch (RendererAPI::get())
		{
			case RendererAPI::API::None  : return nullptr                                            ; break;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture>(path, type, format); break;
		}
	}
}