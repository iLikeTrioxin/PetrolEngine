#pragma once

#include "../VertexArray.h"

namespace PetrolEngine {
	class OpenGLVertexArray : public VertexArray {
	public:
		OpenGLVertexArray();

		void addVertexBuffer(std::shared_ptr<VertexBuffer> vertexBuffer) override;
		void  setIndexBuffer(std::shared_ptr< IndexBuffer>  indexBuffer) override;

		~OpenGLVertexArray();
	};
}