#pragma once

#include <Aliases.h>

namespace PetrolEngine {
	class IndexBufferI {
	public:
		virtual void setData(const void* data, int64 size) = 0;

		virtual ~IndexBufferI() = default;

		NO_DISCARD int64 getID  () const { return ID  ; }
		NO_DISCARD uint  getSize() const { return size; }

	protected:
        int64 size{};
		uint  ID  {};
	};
}