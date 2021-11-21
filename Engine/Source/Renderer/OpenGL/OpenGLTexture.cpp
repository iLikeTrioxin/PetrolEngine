#include <PCH.h>

#include "OpenGLTexture.h"

namespace PetrolEngine {

	OpenGLTexture::OpenGLTexture(int width, int height, TextureType type, TextureFormat format) {
		this->width  = width;
		this->height = height;
		this->format = format;
		this->type   = type;

		if (format == TextureFormat::RED) glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);

		// Those are for DSA version (OpenGL 4.5 or higher)
		//	glCreateTextures(GL_TEXTURE_2D, 1, &id);
		//	glTexStorage2D  (GL_TEXTURE_2D, 1, GLFormat, width, height);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	OpenGLTexture::~OpenGLTexture() {
		glDeleteTextures(1, &id);
	}

	void OpenGLTexture::updateTextureImage(const void* data) {
		auto GLFormat = textureFormatLookupTable.at(format);

		//if(format == TextureFormat::RED) glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glBindTexture(GL_TEXTURE_2D, id);
		
		glTexImage2D(GL_TEXTURE_2D, 0, GLFormat.second, width, height, 0, GLFormat.first, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		// glTextureSubImage2D(id, 0, 0, 0, width, height, GLFormat, GL_UNSIGNED_BYTE, data);
	}

	OpenGLTexture::OpenGLTexture(const Image* image, TextureType type) {
		this->type = type;
		this->id   = 0;

		if (!image->getData()) { LOG("Texture failed to load at path: " + image->getPath(), 2); return; }

		this->width  = image->getWidth();
		this->height = image->getHeight();

		auto GLFormat = textureFormatLookupTable.at( getFormat(image) );
				
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);
		
		// Those are for DSA version (OpenGL 4.5 or higher)
		//	glCreateTextures(GL_TEXTURE_2D, 1, &id);
		//	glTexStorage2D  (GL_TEXTURE_2D, 1, GLFormat, width, height);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S    , GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T    , GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D    (GL_TEXTURE_2D, 0, GLFormat.second, width, height, 0, GLFormat.first, GL_UNSIGNED_BYTE, image->getData());
		glGenerateMipmap(GL_TEXTURE_2D);

		// glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
}