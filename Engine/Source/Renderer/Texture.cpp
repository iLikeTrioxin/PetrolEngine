#include <PCH.h>

#include "OpenGL/OpenGLTexture.h"
#include "Vulkan/VulkanTexture.h"

#include "RendererAPI.h"

namespace PetrolEngine {
	
	Ref<Texture> Texture::create(const String& path, TextureType type) {
	    auto image = Image::create(path);

		switch (RendererAPI::get())
		{
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLTexture>(image, type) ;
            case RendererAPI::API::Vulkan: return CreateRef<VulkanTexture>(image, type);
            default: return nullptr;
        }
	}

	Ref<Texture> Texture::create(const Ref<Image>& image, TextureType type) {
		switch (RendererAPI::get())
		{
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLTexture>(image, type);
            case RendererAPI::API::Vulkan: return CreateRef<VulkanTexture>(image, type);
			default: return nullptr;
		}
	}

	Ref<Texture> Texture::create(int width, int height, TextureType type, TextureFormat format) {
		switch (RendererAPI::get())
		{
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLTexture>(width, height, type, format);
            case RendererAPI::API::Vulkan: return CreateRef<VulkanTexture>(width, height, type, format);
            default: return nullptr;
		}
	}
}