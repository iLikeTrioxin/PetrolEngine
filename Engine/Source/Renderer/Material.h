#pragma once

#include "Texture.h"
#include "Shader.h"
#include <vector>

namespace PetrolEngine {

	class Material {
	public:
		Material() = default;

		std::vector< std::shared_ptr<Texture> > textures;
		std::shared_ptr<Shader> shader;
	};
}

