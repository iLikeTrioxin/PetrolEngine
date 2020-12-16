#include "PrecompiledHeader.h"

#define STB_IMAGE_IMPLEMENTATION

#include "Texture.h"
#include <STB/stb_image.h>

namespace Engine {

	std::vector<Texture> loaded_textures;

	void initalizeTextureSettings(bool flipImage) {
		stbi_set_flip_vertically_on_load(flipImage);
	}

	Texture::Texture(std::string _path, textureType _type) : path(_path), type(_type) {
		bool textureMatched = false;

		for (unsigned int i = 0; i < loaded_textures.size(); i++) {
			if (std::strcmp(loaded_textures[i].path.c_str(), _path.c_str()) == 0) {
				*this = loaded_textures[i];
				textureMatched = true;
				break;
			}
		}
		if (!textureMatched) {
			loadTexture();
			debug_log("id:" << this->id << "\npath:" << this->path << "\ntype:" << this->type << "\nWidth" << this->width << "\nHeight:" << this->height);
			loaded_textures.push_back(*this);
			//std::cout << "id:" << loaded_textures.back().id << "\npath:" << loaded_textures.back().path << "\ntype:" << loaded_textures.back().type << "\nWidth" << loaded_textures.back().width << "\nHeight:" << loaded_textures.back().height << "\n";
		}
	}

	void Texture::loadTexture() {
		unsigned int id;
		int nrComponents;
		int width;
		int height;

		glGenTextures(1, &id);

		unsigned char* data = stbi_load(this->path.c_str(), &width, &height, &nrComponents, 0);
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

		this->id = id;
		this->height = height;
		this->width = width;
	}
	unsigned int Texture::getHeight() {
		return height;
	}
	unsigned int Texture::getWidth() {
		return width;
	}
}