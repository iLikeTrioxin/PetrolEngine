#pragma once

#include <Aliases.h>

// std includes
#include <utility>
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

	static int ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float : return sizeof(float) * 1;
		case ShaderDataType::Float2: return sizeof(float) * 2;
		case ShaderDataType::Float3: return sizeof(float) * 3;
		case ShaderDataType::Float4: return sizeof(float) * 4;

		case ShaderDataType::Mat3: return sizeof(float) * 3 * 3;
		case ShaderDataType::Mat4: return sizeof(float) * 4 * 4;

		case ShaderDataType::Int : return sizeof(int) * 1;
		case ShaderDataType::Int2: return sizeof(int) * 2;
		case ShaderDataType::Int3: return sizeof(int) * 3;
		case ShaderDataType::Int4: return sizeof(int) * 4;

		case ShaderDataType::Bool: return sizeof(bool);
        case ShaderDataType::None: return 0;
        }

		return 0;
	}

	static int GetComponentCount(ShaderDataType type) {
		switch (type) {
            case ShaderDataType::Float :
            case ShaderDataType::Bool  :
            case ShaderDataType::Int   : return 1;
            case ShaderDataType::Float2:
            case ShaderDataType::Int2  : return 2;
            case ShaderDataType::Float3:
            case ShaderDataType::Mat3  :
            case ShaderDataType::Int3  : return 3;
            case ShaderDataType::Float4:
            case ShaderDataType::Mat4  :
            case ShaderDataType::Int4  : return 4;
            default:                     return 0;
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
		Vector<Element> elements;
	};

	class VertexBufferI {
	public:
		virtual ~VertexBufferI() = default;

		//static VertexBufferI* create(RRC creator, const VertexLayout& layout, const void* data = nullptr, int64 size = 0);

		virtual void setData(const void* data, int64 size) = 0;

		NO_DISCARD VertexLayout getLayout() const { return layout; }
		NO_DISCARD unsigned int getID    () const { return ID    ; }

	protected:
		explicit VertexBufferI(VertexLayout layout): layout(move(layout)), ID(0) {};

	protected:
		VertexLayout layout;
		unsigned int ID;
	};
}