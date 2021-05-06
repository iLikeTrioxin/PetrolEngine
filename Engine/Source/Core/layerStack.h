#pragma once

#include <vector>
#include "layer.h"

namespace Engine {
	class LayerStack {
	public:
	private:
		std::vector<Layer> layers;
	};
}