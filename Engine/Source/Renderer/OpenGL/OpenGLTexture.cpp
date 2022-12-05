#include <PCH.h>

#include "OpenGLTexture.h"
#include "../../Atlas.h"
#include "../../Core/Image.h"

namespace PetrolEngine {

	OpenGLTexture::OpenGLTexture(int width, int height, TextureFormat format, TextureType type) {
		this->width  = width;
		this->height = height;
		this->format = format;
        this->type   = type;

		if (format == TextureFormat::RED) glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        auto GLType   = textureTypeLookupTable  .at(type  );
        auto GLFormat = textureFormatLookupTable.at(format);

		glGenTextures(1, &id);
		glBindTexture(GLType, id);

		// Those are for DSA version (OpenGL 4.5 or higher)
		//	glCreateTextures(GL_TEXTURE_2D, 1, &id);
		//	glTexStorage2D  (GL_TEXTURE_2D, 1, GLFormat, width, height);

        if(type == TextureType::Texture2D) {
            if(width && height) glTexImage2D(GL_TEXTURE_2D, 0, GLFormat.second, width, height, 0, GLFormat.first, GL_UNSIGNED_BYTE, nullptr);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        }

        if(type == TextureType::TextureCube){
            for (int i = 0; i < 6; i++) {
                if(width && height)
                    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GLFormat.second, width, height, 0, GLFormat.first, GL_UNSIGNED_BYTE, nullptr);
            }

            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        }

        glBindTexture(GLType, 0);
	}

	OpenGLTexture::~OpenGLTexture() {
		glDeleteTextures(1, &id);
	}

	void OpenGLTexture::updateTextureImage(const void* data, int index = -1) {
		auto GLFormat = textureFormatLookupTable.at(format);
        auto GLType   = textureTypeLookupTable  .at(type  );

        if(!height) LOG("Texture height is 0", 3);
        if(!width ) LOG("Texture width  is 0", 3);

        glBindTexture(GLType, id);

        if(type == TextureType::Texture2D)
            glTexImage2D(GL_TEXTURE_2D, 0, GLFormat.second, width, height, 0, GLFormat.first, GL_UNSIGNED_BYTE, data);

        if(type == TextureType::TextureCube){
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + index, 0, GLFormat.second, width, height, 0, GLFormat.first, GL_UNSIGNED_BYTE, data);

            if(index != -1) goto END;

            for (int i = 0; i < 6; i++)
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GLFormat.second, width, height, 0, GLFormat.first, GL_UNSIGNED_BYTE, data);
        }

		END:glGenerateMipmap(GLType);
	}

	OpenGLTexture::OpenGLTexture(const Image* image) {
		this->id   = 0;

		if (!image->getData()) {
            LOG("Texture failed to load. ", 2); return;
        }

		this->width  = image->getWidth();
		this->height = image->getHeight();

        auto a = getFormat(image);
		auto GLFormat = textureFormatLookupTable.at(a);

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