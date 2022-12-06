#pragma once

#include "Renderer/RendererInterface/Texture.h"

namespace PetrolEngine {

	class VulkanTexture : public Texture {
	public:
		VulkanTexture(
			int width,
			int height,
			TextureFormat format = TextureFormat::NONE
		);

        VulkanTexture(
			const Image* image
		);
		
		~VulkanTexture();

		virtual void updateTextureImage(const void* data) override;
	private:
		const UnorderedMap<TextureFormat, Pair<uint16, uint16>> textureFormatLookupTable{
			{TextureFormat::RGBA16, {GL_RGBA, GL_RGBA16}},
			{TextureFormat::RGBA8 , {GL_RGBA, GL_RGBA8 }},
			{TextureFormat::RGB16 , {GL_RGB , GL_RGB16 }},
			{TextureFormat::RED   , {GL_RED , GL_RED   }}
		};

	};
}