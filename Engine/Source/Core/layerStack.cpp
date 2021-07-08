#include "layerStack.h"

namespace Engine {
	std::vector<std::shared_ptr<Layer>> LayerStack::layers;

	void LayerStack::execute() {
		for (auto layer : layers) { layer->layerBody(); }
	}

	void LayerStack::addLayer(std::shared_ptr<Layer> layer) {
		layers.push_back(layer);
	}

}