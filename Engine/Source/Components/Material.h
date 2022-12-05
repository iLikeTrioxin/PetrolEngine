#pragma once

#include <Aliases.h>

#include "Renderer/RendererInterface/Shader.h"
#include "Renderer/RendererInterface/Texture.h"

namespace PetrolEngine {
	class Material {
	public:
        Material() = default;
        Material(const Ref<Texture>& tex, const Ref<Shader>& shader){
            this->textures.push_back(tex);
            this->shader = shader;
        }
        Material(const Ref<Shader>& shader){
            this->shader = shader;
        }

		Vector<Ref<Texture>> textures;
        Ref<Shader> shader;
	};
}

