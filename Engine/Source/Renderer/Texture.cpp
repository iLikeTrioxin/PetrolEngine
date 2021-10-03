#include <PCH.h>

#include "OpenGL/OpenGLTexture.h"
#include "Vulkan/VulkanTexture.h"

#include "RendererAPI.h"

namespace PetrolEngine {
	
	std::shared_ptr<Texture> Texture::create(const String& path, TextureType type) {
	    auto image = Image(path);

		switch (RendererAPI::get())
		{
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture>(image, type) ;
            case RendererAPI::API::Vulkan: return std::make_shared<VulkanTexture>(image, type);
            default: return nullptr;
        }
	}

	std::shared_ptr<Texture> Texture::create(const Image& image, TextureType type) {
		switch (RendererAPI::get())
		{
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture>(image, type);
            case RendererAPI::API::Vulkan: return std::make_shared<VulkanTexture>(image, type);
			default: return nullptr;
		}
	}

	std::shared_ptr<Texture> Texture::create(int width, int height, TextureType type, TextureFormat format) {
		switch (RendererAPI::get())
		{
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture>(width, height, type, format);
            case RendererAPI::API::Vulkan: return std::make_shared<VulkanTexture>(width, height, type, format);
            default: return nullptr;
		}
	}
}