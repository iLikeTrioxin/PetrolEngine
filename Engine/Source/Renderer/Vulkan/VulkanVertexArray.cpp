#include <PCH.h>

#include "VulkanVertexArray.h"

namespace Engine {
	static GLenum ShaderDataTypeToVulkanBaseType(ShaderDataType type) {
		switch (type)
		{
		case ShaderDataType::Float : return GL_FLOAT;
		case ShaderDataType::Float2: return GL_FLOAT;
		case ShaderDataType::Float3: return GL_FLOAT;
		case ShaderDataType::Float4: return GL_FLOAT;

		case ShaderDataType::Mat3: return GL_FLOAT;
		case ShaderDataType::Mat4: return GL_FLOAT;
		
		case ShaderDataType::Int : return GL_INT;
		case ShaderDataType::Int2: return GL_INT;
		case ShaderDataType::Int3: return GL_INT;
		case ShaderDataType::Int4: return GL_INT;
		
		case ShaderDataType::Bool: return GL_BOOL;
		}
	}

	VulkanVertexArray::VulkanVertexArray() {
		LOG_FUNCTION();
		
		glGenVertexArrays(1, &ID);
	}

	void VulkanVertexArray::setIndexBuffer(std::shared_ptr<IndexBuffer> indexBuffer) {
		LOG_FUNCTION();
		
		glBindVertexArray(this->ID);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer->getID());

		this->indexBuffer = indexBuffer;
	}

	void VulkanVertexArray::addVertexBuffer(std::shared_ptr<VertexBuffer> vertexBuffer) {
		LOG_FUNCTION();

		glBindVertexArray(ID);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer->getID());
	
		auto vertexLayout = vertexBuffer->getLayout();
		
		uint32_t layoutSize = 0;
		for (auto& element : vertexLayout.elements) layoutSize += ShaderDataTypeSize(element.type);
		
		uint32_t offset = 0;
		uint32_t index  = 0;
		for ( auto& element : vertexLayout.elements ) {
			switch (auto& type = element.type)
			{
			case ShaderDataType::None: debug_log("[!] None type element detected in vertex array."); break;

			case ShaderDataType::Mat3:
			case ShaderDataType::Mat4: {
				int8_t count = GetComponentCount(type);

				for (uint8_t i = 0; i < count; i++)
				{
					glEnableVertexAttribArray(index);

					glVertexAttribPointer(
						index,
						count,
						ShaderDataTypeToVulkanBaseType(type),
						GL_FALSE,
						layoutSize,
						(void*)(offset + (sizeof(float) * count * i))
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

	VulkanVertexArray::~VulkanVertexArray() {
		LOG_FUNCTION();

		glDeleteBuffers(1, &ID);
	}
}