#pragma once

#include "../VertexArray.h"

namespace PetrolEngine {
	class OpenGLVertexArray : public VertexArray {
	public:
		OpenGLVertexArray();

		void addVertexBuffer(VertexBuffer* vertexBuffer) override;
		void  setIndexBuffer( IndexBuffer*  indexBuffer) override;

		~OpenGLVertexArray();
	};
}