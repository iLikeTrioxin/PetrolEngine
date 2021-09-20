#pragma once

// std includes
#include <vector>
#include <memory>

namespace PetrolEngine {
	class IndexBuffer {
	public:
		static std::shared_ptr<IndexBuffer> create();
		static std::shared_ptr<IndexBuffer> create(void* data, uint32_t size);

		virtual void setData(void* data, uint32_t size) = 0;

		virtual ~IndexBuffer() = default;

		uint32_t getID  () const { return ID  ; }
		uint32_t getSize() const { return size; }

	protected:
		uint32_t size;
		uint32_t ID;
	};
}