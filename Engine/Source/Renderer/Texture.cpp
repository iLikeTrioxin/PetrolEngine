#include "../PCH.h"

#include "Texture.h"
#include "OpenGL/OpenGLTexture.h"
#include "Renderer.h"

namespace Engine {
	
	std::shared_ptr<Texture> Texture::create(std::string path, TextureType type) {
		switch (RendererAPI::get())
		{
			case RendererAPI::API::None  : return nullptr                                            ; break;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture>(Image(path), type) ; break;
		}
	}

	std::shared_ptr<Texture> Texture::create(Image& image, TextureType type) {
		switch (RendererAPI::get())
		{
			case RendererAPI::API::None  : return nullptr; break;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture>(image, type); break;
		}
	}

	std::shared_ptr<Texture> Texture::create(int width, int height, TextureType type, TextureFormat format) {
		switch (RendererAPI::get())
		{
			case RendererAPI::API::None  : return nullptr                                                     ; break;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture>(width, height, type, format); break;
		}
	}
}