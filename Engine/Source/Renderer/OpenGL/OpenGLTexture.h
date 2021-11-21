#pragma once

#include "../Texture.h"

namespace PetrolEngine {

	void initializeTextureSettings(bool flipImage);

	class OpenGLTexture : public Texture {
	public:
		OpenGLTexture(
			int width,
			int height,
			TextureType   type   = TextureType  ::NONE,
			TextureFormat format = TextureFormat::NONE
		);

        OpenGLTexture(
			const Image* image,
			TextureType type
		);
		
		~OpenGLTexture() override;

		void updateTextureImage(const void* data) override;
	private:
		const UnorderedMap<TextureFormat, Pair<GLuint, GLuint>> textureFormatLookupTable{
			{TextureFormat::RGBA16, {GL_RGBA, GL_RGBA16}},
			{TextureFormat::RGBA8 , {GL_RGBA, GL_RGBA8 }},
			{TextureFormat::RGB16 , {GL_RGB , GL_RGB16 }},
			{TextureFormat::RED   , {GL_RED , GL_RED   }}
		};
	};
}