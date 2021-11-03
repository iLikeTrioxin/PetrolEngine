#pragma once

#include "layer.h"

#include <vector>
#include <memory>

#include <Aliases.h>

namespace PetrolEngine {
	class LayerStack {
	public:
		static void execute();
		static void addLayer(Ref<Layer> layer);

	private:
		static std::vector<Ref<Layer>> layers;
	};
}