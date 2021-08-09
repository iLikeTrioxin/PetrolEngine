#pragma once

#include "../Texture.h"

//
// Messy code - repair it
//

namespace Engine {

	void initalizeTextureSettings(bool flipImage);

	class OpenGLTexture : public Texture {
	public:
		OpenGLTexture(
			int width,
			int height,
			TextureType   type   = TextureType  ::NONE,
			TextureFormat format = TextureFormat::NONE
		);

		OpenGLTexture(
			Image& image,
			TextureType type = TextureType::NONE
		);
		
		~OpenGLTexture();

		virtual void updateTextureImage(const void* data) override;
	private:
		const std::unordered_map<TextureFormat, std::pair<GLuint, GLuint>> textureFormatLookupTable{
			{TextureFormat::RGBA16, {GL_RGBA, GL_RGBA16}},
			{TextureFormat::RGBA8 , {GL_RGBA, GL_RGBA8 }},
			{TextureFormat::RGB16 , {GL_RGB , GL_RGB16 }},
			{TextureFormat::RED   , {GL_RED , GL_RED   }}
		};
		//void updateTextureImage(TextureFormat format, unsigned int width, unsigned int height, const void* data);
		void createTexture();
		//void loadTexture(const char* path);
	};
}