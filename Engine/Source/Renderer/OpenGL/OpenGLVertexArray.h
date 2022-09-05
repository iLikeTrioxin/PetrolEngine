#pragma once

#include "Renderer/RendererInterface/VertexArrayI.h"

namespace PetrolEngine {
	class OpenGLVertexArray : public VertexArrayI {
	public:
		OpenGLVertexArray();

		void addVertexBuffer(Ref<VertexBufferI> vertexBuffer) override;
		void  setIndexBuffer(Ref<IndexBufferI >  indexBuffer) override;

		~OpenGLVertexArray() override;
	};
}