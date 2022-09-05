#pragma once

#include <Aliases.h>

#include "Renderer/RendererInterface/ShaderI.h"
#include "Renderer/RendererInterface/TextureI.h"

namespace PetrolEngine {
	class Material {
	public:
        Material() = default;
        Material(const Ref<TextureI>& tex, const Ref<ShaderI>& shader){
            this->textures.push_back(tex);
            this->shader = shader;
        }
        Material(const Ref<ShaderI>& shader){
            this->shader = shader;
        }

		Vector<Ref<TextureI>> textures;
        Ref<ShaderI> shader;
	};
}

