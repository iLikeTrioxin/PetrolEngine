#pragma once

#include "../VertexArray.h"

namespace PetrolEngine {
	class OpenGLVertexArray : public VertexArray {
	public:
		OpenGLVertexArray();

		virtual void addVertexBuffer(std::shared_ptr<VertexBuffer> vertexBuffer) override;
		virtual void  setIndexBuffer(std::shared_ptr< IndexBuffer>  indexBuffer) override;

		~OpenGLVertexArray();
	};
}