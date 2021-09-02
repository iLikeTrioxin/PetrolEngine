#include "Texture.h"
#include "OpenGL/OpenGLTexture.h"
#include "RendererAPI.h"

namespace Engine {
	
	std::shared_ptr<Texture> Texture::create(const std::string& path, TextureType type) {
	    auto image = Image(path);
		switch (RendererAPI::get())
		{
			case RendererAPI::API::None  : return nullptr                                         ;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture>(image, type) ;
		}
	}

	std::shared_ptr<Texture> Texture::create(const Image& image, TextureType type) {
		switch (RendererAPI::get())
		{
			case RendererAPI::API::None  : return nullptr;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture>(image, type);
		}
	}

	std::shared_ptr<Texture> Texture::create(int width, int height, TextureType type, TextureFormat format) {
		switch (RendererAPI::get())
		{
			case RendererAPI::API::None  : return nullptr                                                     ;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture>(width, height, type, format);
		}
	}
}