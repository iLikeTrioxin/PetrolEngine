#pragma once

#include "../IndexBuffer.h"

namespace Engine {
	class OpenGLIndexBuffer : public IndexBuffer {
	public:
		OpenGLIndexBuffer();
		OpenGLIndexBuffer(void* data, uint32_t size);

		virtual void setData(void* data, uint32_t size) override;

		~OpenGLIndexBuffer();
	};
}