#pragma once

#include <memory>

namespace Engine {

	/// <summary>
	/// Interface for setting loader for graphics API 
	/// </summary>
	class GraphicsContext {
	public:
		virtual ~GraphicsContext() = default;
		
		virtual int init(void* loaderProc = nullptr) = 0;

		static std::unique_ptr<GraphicsContext> create(void* window);
	};
}