#include <PCH.h>

#include "OpenGLVertexArray.h"

namespace PetrolEngine {
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
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

	OpenGLVertexArray::OpenGLVertexArray() { LOG_FUNCTION();
		glGenVertexArrays(1, &ID);
	}

	void OpenGLVertexArray::setIndexBuffer(IndexBuffer*& indexBuffer) { LOG_FUNCTION();
		glBindVertexArray(this->ID);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer->getID());

		this->indexBuffer = indexBuffer;
        indexBuffer = nullptr;
        glBindVertexArray(0);
	}

	void OpenGLVertexArray::addVertexBuffer(VertexBuffer*& vertexBuffer) { LOG_FUNCTION();
		glBindVertexArray(this->ID);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer->getID());

        auto vertexLayout = vertexBuffer->getLayout();
		
		int layoutSize = 0;
		for (auto& element : vertexLayout.getElements()) layoutSize += ShaderDataTypeSize(element.type);
		
		uint64 offset = 0;
		uint32 index  = 0;
		for ( auto& element : vertexLayout.getElements() ) {
			switch (auto& type = element.type)
			{
			    case ShaderDataType::None: LOG("None type element detected in vertex array.", 2); break;
			    case ShaderDataType::Mat3:
			    case ShaderDataType::Mat4: {
			    	int count = GetComponentCount(type);

			    	for (uint i = 0; i < count; i++)
			    	{
			    		glEnableVertexAttribArray(index);

			    		glVertexAttribPointer(
			    			index,
			    			count,
			    			ShaderDataTypeToOpenGLBaseType(type),
			    			GL_FALSE,
			    			layoutSize,
			    			(void*)(offset + (sizeof(float) * (uint)count * i))
			    		);

			    		glVertexAttribDivisor(index, 1);
			    		index++;
			    	}

			    	offset += ShaderDataTypeSize(type);
			    	continue;
			    }
			    case ShaderDataType::Float :
			    case ShaderDataType::Float2:
			    case ShaderDataType::Float3:
			    case ShaderDataType::Float4: {
			    	glEnableVertexAttribArray(index);

			    	glVertexAttribPointer(
			    		index,
			    		GetComponentCount(type),
			    		ShaderDataTypeToOpenGLBaseType(type),
			    		GL_FALSE,
			    		layoutSize,
			    		(void*)offset
			    	);

			    	offset += ShaderDataTypeSize(type);
			    	index++;
			    	continue;
			    }
			    case ShaderDataType::Int :
			    case ShaderDataType::Int2:
			    case ShaderDataType::Int3:
			    case ShaderDataType::Int4:
			    case ShaderDataType::Bool: {
			    	glEnableVertexAttribArray(index);

			    	glVertexAttribIPointer(
			    		index,
			    		GetComponentCount(type),
			    		ShaderDataTypeToOpenGLBaseType(type),
			    		layoutSize,
			    		(void*)offset
			    	);

			    	offset += ShaderDataTypeSize(type);
			    	index++;
			    	continue;
			    }
			}
		}

		this->vertexBuffers.push_back(vertexBuffer);
        vertexBuffer = nullptr;
        glBindVertexArray(0);
	}

	OpenGLVertexArray::~OpenGLVertexArray() { LOG_FUNCTION();
        for(auto& vertexBuffer : vertexBuffers)
            delete vertexBuffer;

        delete indexBuffer;

		glDeleteBuffers(1, &ID);
	}
}