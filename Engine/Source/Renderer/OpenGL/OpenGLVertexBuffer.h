#pragma once

#include "../VertexBuffer.h"

namespace Engine {
	class OpenGLVertexBuffer : public VertexBuffer {
	public:
		OpenGLVertexBuffer(VertexLayout layout);
		OpenGLVertexBuffer(VertexLayout layout, void* data, uint32_t size);

		virtual void setData(void* data, uint32_t size) override;

		~OpenGLVertexBuffer();
	};
}