#include <PCH.h>

#include "VulkanVertexArray.h"

namespace PetrolEngine {
	static GLenum ShaderDataTypeToVulkanBaseType(ShaderDataType type) {
		switch (type) {
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

		    case ShaderDataType::Bool  : return GL_BOOL;
            default                    : return GL_NONE;
        }
	}

	VulkanVertexArray::VulkanVertexArray() { LOG_FUNCTION();
		glGenVertexArrays(1, &ID);
	}

	void VulkanVertexArray::setIndexBuffer(Ref<IndexBuffer> indexBuffer) { LOG_FUNCTION(); //-V688
		glBindVertexArray(this->ID);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer->getID());

		this->indexBuffer = indexBuffer;
	}

	void VulkanVertexArray::addVertexBuffer(Ref<VertexBuffer> vertexBuffer) { LOG_FUNCTION();
		glBindVertexArray(ID);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer->getID());

		auto vertexLayout = vertexBuffer->getLayout();
		
		int layoutSize = 0;
		for (auto& element : vertexLayout.elements) layoutSize += ShaderDataTypeSize(element.type);
		
        uint64 offset = 0;
		uint32 index  = 0;
		for ( auto& element : vertexLayout.elements ) {
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
						ShaderDataTypeToVulkanBaseType(type),
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
					ShaderDataTypeToVulkanBaseType(type),
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
					ShaderDataTypeToVulkanBaseType(type),
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
	}

	VulkanVertexArray::~VulkanVertexArray() { LOG_FUNCTION();
		glDeleteBuffers(1, &ID);
	}
}