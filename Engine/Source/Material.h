#pragma once

#include "Texture.h"
#include "Shader.h"
#include <vector>

namespace Engine{

	class Material
	{
	public:
		std::vector<Texture> textures;
		Shader* shader;
	};
}

