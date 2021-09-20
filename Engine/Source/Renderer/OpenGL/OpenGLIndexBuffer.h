#pragma once

#include "../IndexBuffer.h"

namespace PetrolEngine {
	class OpenGLIndexBuffer : public IndexBuffer {
	public:
		OpenGLIndexBuffer();
		OpenGLIndexBuffer(void* data, uint32_t size);

		virtual void setData(void* data, uint32_t size) override;

		~OpenGLIndexBuffer();
	};
}