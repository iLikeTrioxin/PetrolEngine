#pragma once

#include "Renderer/RendererInterface/VertexBufferI.h"

namespace PetrolEngine {
	class OpenGLVertexBuffer : public VertexBufferI {
	public:
		OpenGLVertexBuffer(VertexLayout layout);
		OpenGLVertexBuffer(VertexLayout layout, const void* data, int64 size);

		virtual void setData(const void* data, int64 size) override;

		~OpenGLVertexBuffer() override;
	};
}