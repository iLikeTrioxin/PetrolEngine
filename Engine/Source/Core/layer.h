#pragma once

#include <vector>

namespace PetrolEngine {
	class Layer {
	public:
		virtual void layerBody() = 0;

		~Layer() = default;
	private:

	};
}