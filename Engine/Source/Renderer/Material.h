#pragma once

#include "Texture.h"
#include "Shader.h"
#include <vector>

namespace PetrolEngine {

	class Material {
	public:
		Material() = default;

		std::vector< Ref<Texture> > textures;
		Ref<Shader> shader;
	};
}

