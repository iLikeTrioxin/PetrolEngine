#include "../../PCH.h"

#include "OpenGLTexture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <Stb/stb_image.h>

//#define STB_IMAGE_WRITE_IMPLEMENTATION
//#include <Stb/stb_image_write.h>

namespace Engine {

	OpenGLTexture::OpenGLTexture(std::string path, TextureType type, TextureFormat format){
		this->type   = type;
		this->format = format;

		loadTexture(path.c_str());
	}
	void OpenGLTexture::createTexture() {
		glGenTextures(1, &id);
	}
	//void OpenGLTexture::updateTextureImage(TextureFormat format, unsigned int width, unsigned int height, const void* data) {
	//	auto GLFormat = textureFormatLookupTable.find(format)->second;
	//	
	//	glTextureSubImage2D(id, 0, 0, 0, width, height, GLFormat, GL_UNSIGNED_BYTE, data);
	//}
	void OpenGLTexture::loadTexture(const char* path) {
		int nrComponents;
		
		stbi_set_flip_vertically_on_load(1);

		unsigned char* data = stbi_load(path, (int*)&width, (int*)&height, &nrComponents, 0);

		if ( data && !stbi_failure_reason() ) {
			GLenum format;

			if (nrComponents == 1)
				format = GL_RED;
			else if (nrComponents == 3)
				format = GL_RGB;
			else if (nrComponents == 4)
				format = GL_RGBA; 

			glGenTextures(1, &id);
			
			glBindTexture(GL_TEXTURE_2D, id);
			
			//glCreateTextures(GL_TEXTURE_2D, 1, &id);
			//glTextureStorage2D(id, 1, GL_RGBA8, width, height);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
			//glTextureSubImage2D(id, 0, 0, 0, width, height, format, GL_UNSIGNED_BYTE, data);
			
			stbi_image_free(data);
		}
		else {
			debug_log("[!] Texture failed to load at path: " << path);
			stbi_image_free(data);
		}
	}
}