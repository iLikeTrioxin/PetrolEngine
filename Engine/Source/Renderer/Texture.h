#pragma once

namespace Engine {

	void initalizeTextureSettings(bool flipImage);

	enum TextureType {
		NONE     = 0,
		DIFFUSE  = 1,
		NORMAL   = 2,
		HEIGHT   = 3,
		SPECULAR = 4
	};

	enum class TextureFormat {
		NONE,

		// color formats
		RGBA16UI,
		RGBA8UI,

		RGBA16F,
		RGBA32F,

		RGBA8,
		RGBA16,

		RGB8,
		RGB8UI,
		RGB16,
		RGB16UI,

		RG8,
		RG8UI,
		RG16,
		RG16UI,

		// Depth formats
		DEPTH16,
		DEPTH24,
		DEPTH32,
		DEPTH32F,

		// Depth-Stencil formats
		DEPTH24_STENCIL8,
		DEPTH32F_STENCIL8,

		// Stencil only
		STENCIL_INDEX8,
	};


	class Texture {
	public:
		TextureFormat format;
		TextureType type;

		virtual ~Texture() = default;

		unsigned int getHeight() { return height; };
		unsigned int getWidth () { return width ; };

		unsigned int getID() {
			return id;
		}

		static std::shared_ptr<Texture> load(std::string path = "", TextureType type = TextureType::NONE, TextureFormat format = TextureFormat::NONE);

		static std::shared_ptr<Texture> create(std::string path = "", TextureType type = TextureType::NONE, TextureFormat format = TextureFormat::NONE);
	protected:
		unsigned int id;
		unsigned int width = 0;
		unsigned int height = 0;

		static std::unordered_map<std::string, std::shared_ptr<Texture>> loadedTextures;
	};
}