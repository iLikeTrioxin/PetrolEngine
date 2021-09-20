#pragma once

// std includes
#include <vector>
#include <memory>

namespace PetrolEngine {

    enum class ShaderDataType {
		None = 0,

		Float,
		Float2,
		Float3,
		Float4,

		Mat3,
		Mat4,

		Int,
		Int2,
		Int3,
		Int4,

		Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float: return sizeof(float) * 1;
		case ShaderDataType::Float2: return sizeof(float) * 2;
		case ShaderDataType::Float3: return sizeof(float) * 3;
		case ShaderDataType::Float4: return sizeof(float) * 4;

		case ShaderDataType::Mat3: return sizeof(float) * 3 * 3;
		case ShaderDataType::Mat4: return sizeof(float) * 4 * 4;

		case ShaderDataType::Int: return sizeof(int) * 1;
		case ShaderDataType::Int2: return sizeof(int) * 2;
		case ShaderDataType::Int3: return sizeof(int) * 3;
		case ShaderDataType::Int4: return sizeof(int) * 4;

		case ShaderDataType::Bool: return sizeof(bool);
		}

		return 0;
	}

	static uint32_t GetComponentCount(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:   return 1;
		case ShaderDataType::Float2:  return 2;
		case ShaderDataType::Float3:  return 3;
		case ShaderDataType::Float4:  return 4;
		case ShaderDataType::Mat3:    return 3; // 3* float3
		case ShaderDataType::Mat4:    return 4; // 4* float4
		case ShaderDataType::Int:     return 1;
		case ShaderDataType::Int2:    return 2;
		case ShaderDataType::Int3:    return 3;
		case ShaderDataType::Int4:    return 4;
		case ShaderDataType::Bool:    return 1;
		}
	}

	class VertexLayout {
	public:
		struct Element {
			std::string    name;
			ShaderDataType type;
		};

		VertexLayout(std::initializer_list<Element> elements) : elements(elements) {};

	public:
		std::vector<Element> elements;
	};

	class VertexBuffer {
	public:
		virtual ~VertexBuffer() = default;

		static std::shared_ptr<VertexBuffer> create(VertexLayout layout);
		static std::shared_ptr<VertexBuffer> create(VertexLayout layout, void* data, uint32_t size);
		
		virtual void setData(void* data, uint32_t size) = 0;

		VertexLayout getLayout() const { return layout; }
		uint32_t     getID    () const { return ID    ; }

	protected:
		VertexBuffer(VertexLayout layout): layout(layout), ID(0) {};

	protected:
		VertexLayout layout;
		uint32_t ID;
	};
}