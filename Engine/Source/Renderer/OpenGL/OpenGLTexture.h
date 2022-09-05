#pragma once

#include "Renderer/RendererInterface/TextureI.h"

namespace PetrolEngine {

	class OpenGLTexture : public TextureI {
	public:
		OpenGLTexture(
			int width,
			int height,
			TextureFormat format = TextureFormat::NONE
		);

        OpenGLTexture(
			const Image* image,
            int a= GL_UNSIGNED_BYTE
		);
		
		~OpenGLTexture() override;

		void updateTextureImage(const void* data) override;
	private:
		const UnorderedMap<TextureFormat, Pair<uint16, uint16>> textureFormatLookupTable{
			{TextureFormat::RGBA16, {GL_RGBA, GL_RGBA16}},
			{TextureFormat::RGBA8 , {GL_RGBA, GL_RGBA8 }},
			{TextureFormat::RGB16 , {GL_RGB , GL_RGB16 }},
			{TextureFormat::RED   , {GL_RED , GL_RED   }}
		};
	};
}