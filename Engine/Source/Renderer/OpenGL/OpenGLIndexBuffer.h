#pragma once

#include "../IndexBuffer.h"

namespace PetrolEngine {
	class OpenGLIndexBuffer : public IndexBuffer {
	public:
		OpenGLIndexBuffer();
		OpenGLIndexBuffer(const void* data, int64 size);

        void setData(const void* data, int64 size) override;

		~OpenGLIndexBuffer() override;
	};
}