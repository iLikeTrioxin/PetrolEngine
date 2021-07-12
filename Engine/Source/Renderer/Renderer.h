#pragma once

#include <memory>
#include "../Components.h"
#include "../DebugTools.h"

namespace Engine {

	/// <summary>
	/// Graphics API interface for Renderer.
	/// It cannot be integrated with Renderer becouse it's functions are static.
	/// </summary>
	class RendererAPI {
	public:
		enum class API {
			None = 0,
			OpenGL = 1
		};

	public:
		static std::unique_ptr<RendererAPI> create();
		
		virtual int  init    () = 0;
		virtual void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void renderMesh (Mesh& mesh, Transform& transform, Camera& camera) = 0;
		virtual void clear() = 0;

		virtual ~RendererAPI() = default;

		static API get() { return currentAPI; };

	private:
		static API currentAPI;
	};

	class Renderer {
	public:
		static Renderer& get() { return renderer; };
		static int       init() { return rendererAPI->init(); };
		//static Shader&   loadShader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
		static void renderMesh(Mesh& mesh, Transform& transform, Camera& camera) { LOG_FUNCTION(); rendererAPI->renderMesh(mesh, transform, camera); };
		static void OnWindowResize(uint32_t width, uint32_t   height) { LOG_FUNCTION(); rendererAPI->setViewport(0, 0, width, height); };

		static void clear() { LOG_FUNCTION(); rendererAPI->clear(); }

		static void setClearColor(float red, float green, float blue, float alpha);
	private:
		Renderer() { rendererAPI = RendererAPI::create(); }
		static std::unique_ptr<RendererAPI> rendererAPI;
		static Renderer renderer;
		//void internalCameraUpdate(Camera& camera);
	};
}
