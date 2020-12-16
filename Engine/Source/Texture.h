#pragma once

namespace Engine {

	void initalizeTextureSettings(bool flipImage);

	enum textureType {
		NONE     = 0,
		DIFFUSE  = 1,
		NORMAL   = 2,
		HEIGHT   = 3,
		SPECULAR = 4
	};

	class Texture {
	public:
		unsigned int id;
		textureType type;
		std::string path;

		Texture(std::string path = " ", textureType type = textureType::NONE);

		unsigned int getHeight();
		unsigned int getWidth();

	private:
		unsigned int width = 0;
		unsigned int height = 0;

		void loadTexture();
	};
}