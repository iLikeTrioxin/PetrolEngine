#pragma once

#include <vector>

namespace Engine {
	class Layer {
	public:
		virtual void layerBody() = 0;

		~Layer() = default;
	private:

	};
}