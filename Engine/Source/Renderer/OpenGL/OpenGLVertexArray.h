#pragma once

#include "../VertexArray.h"

namespace PetrolEngine {
	class OpenGLVertexArray : public VertexArray {
	public:
		OpenGLVertexArray();

		void addVertexBuffer(Ref<VertexBuffer> vertexBuffer) override;
		void  setIndexBuffer(Ref< IndexBuffer>  indexBuffer) override;

		~OpenGLVertexArray();
	};
}