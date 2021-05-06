#include "../../PCH.h"

#include "OpenGLTexture.h"
#include <STB/stb_image.h>

namespace Engine {

	OpenGLTexture::OpenGLTexture(const char* path) {
		loadTexture(path);
	}
	void OpenGLTexture::createTexture() {
		glGenTextures(1, &id);
	}
	void OpenGLTexture::updateTextureImage(TextureFormat format, unsigned int width, unsigned int height, const void* data) {
		auto GLFormat = textureFormatLookupTable.find(format)->second;
		
		glTextureSubImage2D(id, 0, 0, 0, width, height, GLFormat, GL_UNSIGNED_BYTE, data);
	}
	void OpenGLTexture::loadTexture(const char* path) {
		int nrComponents;
		
		glGenTextures(1, &id);

		unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
		if (data) {
			GLenum format;

			if (nrComponents == 1)
				format = GL_RED;
			else if (nrComponents == 3)
				format = GL_RGB;
			else if (nrComponents == 4)
				format = GL_RGBA; 

			glBindTexture(GL_TEXTURE_2D, id);
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			//glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			stbi_image_free(data);
		}
		else {
			std::cout << "[!] Texture failed to load at path: " << path << std::endl;
			stbi_image_free(data);
		}
	}
}