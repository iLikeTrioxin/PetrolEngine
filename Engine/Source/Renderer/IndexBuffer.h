#pragma once

#include "RendererResourceCreator.h"

// std includes
#include <vector>
#include <memory>

namespace PetrolEngine {
	class IndexBuffer {
	public:
		static IndexBuffer* create(RRC creator, const void* data = nullptr, int64 size = 0);

		virtual void setData(const void* data, int64 size) = 0;

		virtual ~IndexBuffer() = 0;

		NO_DISCARD int64 getID  () const { return ID  ; }
		NO_DISCARD uint  getSize() const { return size; }

	protected:
        int64 size{};
		uint  ID  {};
	};
}