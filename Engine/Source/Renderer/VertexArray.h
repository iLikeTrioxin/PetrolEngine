#pragma once

// std includes
#include <stdint.h>
#include <string>
#include <vector>

#include "RendererResourceCreator.h"

#include "VertexBuffer.h"
#include  "IndexBuffer.h"

namespace PetrolEngine {
	class VertexArray {
	public:
		static VertexArray* create(RRC creator);

		virtual void addVertexBuffer(VertexBuffer* vertexBuffer) = 0;
		virtual void  setIndexBuffer( IndexBuffer*  indexBuffer) = 0;

		virtual ~VertexArray() = 0;

		uint32 getID() { return ID; }

	protected:
		Vector<VertexBuffer*> vertexBuffers;
		        IndexBuffer*   indexBuffer;

		uint32 ID;
	};
}