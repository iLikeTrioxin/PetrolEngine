#pragma once

#include "Entity.h"

namespace Engine {
	class vertexBuffer {
	public:
		virtual ~vertexBuffer() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

	};
	class indexBuffer {

	};
}
