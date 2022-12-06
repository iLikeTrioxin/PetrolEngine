#include <PCH.h>

#include "MetalVertexArray.h"

namespace PetrolEngine {
	static GLenum ShaderDataTypeToMetalBaseType(ShaderDataType type) {
		switch (type)
		{
            case ShaderDataType::Bool  : return GL_BOOL;
            case ShaderDataType::Float :
            case ShaderDataType::Float2:
            case ShaderDataType::Float3:
            case ShaderDataType::Float4:
            case ShaderDataType::Mat3  :
            case ShaderDataType::Mat4  : return GL_FLOAT;
            case ShaderDataType::Int   :
            case ShaderDataType::Int2  :
            case ShaderDataType::Int3  :
            case ShaderDataType::Int4  : return GL_INT;
            default                    : return GL_NONE;
        }
	}

	MetalVertexArray::MetalVertexArray() {
        LOG_FUNCTION();
	}

	void MetalVertexArray::setIndexBuffer(IndexBuffer*& indexBuffer) {
        LOG_FUNCTION();
	}

	void MetalVertexArray::addVertexBuffer(VertexBuffer*& vertexBuffer) {
        LOG_FUNCTION();
	}

	MetalVertexArray::~MetalVertexArray() {
        LOG_FUNCTION();
	}
}