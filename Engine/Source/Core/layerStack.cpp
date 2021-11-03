#include "layerStack.h"

namespace PetrolEngine {
	std::vector<Ref<Layer>> LayerStack::layers;

	void LayerStack::execute() {
		for (auto layer : layers) { layer->layerBody(); }
	}

	void LayerStack::addLayer(Ref<Layer> layer) {
		layers.push_back(layer);
	}

}