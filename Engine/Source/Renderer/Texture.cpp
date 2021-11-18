#include <PCH.h>

#include "Texture.h"

namespace PetrolEngine {
	/*
	Ref<Texture> Texture::create(const String& path, TextureType type) {
	    auto image = Image::create(path);

		switch (RendererAPI::get())
		{
			case RendererAPI::API::OpenGL: return createRef<OpenGLTexture>(image, type) ;
            case RendererAPI::API::Vulkan: return createRef<VulkanTexture>(image, type);
            default: return nullptr;
        }
	}

	Ref<Texture> Texture::create(const Ref<Image>& image, TextureType type) {
		switch (RendererAPI::get())
		{
			case RendererAPI::API::OpenGL: return createRef<OpenGLTexture>(image, type);
            case RendererAPI::API::Vulkan: return createRef<VulkanTexture>(image, type);
			default: return nullptr;
		}
	}

	Ref<Texture> Texture::create(int width, int height, TextureType type, TextureFormat format) {
		switch (RendererAPI::get())
		{
			case RendererAPI::API::OpenGL: return createRef<OpenGLTexture>(width, height, type, format);
            case RendererAPI::API::Vulkan: return createRef<VulkanTexture>(width, height, type, format);
            default: return nullptr;
		}
	}
    */
    Texture* Texture::create(RRC creator, const Image* image, TextureType type) {
        return creator.newTexture(image, type);
    }
}