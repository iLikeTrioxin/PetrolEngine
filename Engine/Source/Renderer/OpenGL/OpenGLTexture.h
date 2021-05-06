#pragma once

#include "../Texture.h"

namespace Engine {

	void initalizeTextureSettings(bool flipImage);

	class OpenGLTexture : public Texture {
	public:

		OpenGLTexture(const char* path);
		~OpenGLTexture();

	private:
		const std::unordered_map<TextureFormat, unsigned int> textureFormatLookupTable{
			{TextureFormat::RGBA16, GL_RGBA16},
			{TextureFormat::RGB16 , GL_RGB16 }
		};
		void updateTextureImage(TextureFormat format, unsigned int width, unsigned int height, const void* data);
		virtual void createTexture() override;
		virtual void loadTexture(const char* path) override;
	};
}