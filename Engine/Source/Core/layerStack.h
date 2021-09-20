#pragma once

#include <vector>
#include "layer.h"
#include <memory>

namespace PetrolEngine {
	class LayerStack {
	public:
		static void execute();
		static void addLayer(std::shared_ptr<Layer> layer);

	private:
		static std::vector<std::shared_ptr<Layer>> layers;
	};
}