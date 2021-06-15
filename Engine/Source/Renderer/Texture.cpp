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
		std::shared_ptr<Texture> result;
		
		switch (RendererAPI::get())
		{
		case RendererAPI::API::None: result = nullptr; break;
		case RendererAPI::API::OpenGL: result = std::make_shared<OpenGLTexture>(path); break;
		}
		
		if (result == nullptr)
			return nullptr;

		

		return result;
	}
}