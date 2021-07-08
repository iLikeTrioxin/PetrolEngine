#pragma once

#include "Texture.h"
#include "Shader.h"
#include <vector>

namespace Engine{

	class Material
	{
	public:
		std::vector< std::shared_ptr<Texture> > textures;
		std::shared_ptr<Shader> shader;
	};
}

