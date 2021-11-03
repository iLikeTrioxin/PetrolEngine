#pragma once

// std includes
#include <vector>
#include <memory>

namespace PetrolEngine {
	class IndexBuffer {
	public:
		static Ref<IndexBuffer> create();
		static Ref<IndexBuffer> create(const void* data, int64 size);

		virtual void setData(const void* data, int64 size) = 0;

		virtual ~IndexBuffer() = default;

		NO_DISCARD int64 getID  () const { return ID  ; }
		NO_DISCARD uint  getSize() const { return size; }

	protected:
        int64 size{};
		uint  ID  {};
	};
}