#pragma once

#include <memory>
#include "OpenGL/OpenGLRenderer.h"
#include "../Components.h"
#include "../DebugTools.h"

namespace Engine {
	class Renderer {
	public:
		static Renderer& get() { return renderer; };
		static int init() { return rendererAPI->init(); }
		//static Shader&   loadShader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
		static void renderMesh    (Mesh&    mesh , Transform& transform) { LOG_FUNCTION(); rendererAPI->renderMesh (mesh, transform    ); };
		static void OnWindowResize(uint32_t width, uint32_t   height   ) { LOG_FUNCTION(); rendererAPI->setViewport(0, 0, width, height); };
		
		static void clear() { LOG_FUNCTION(); rendererAPI->clear(); }
		
		static void setClearColor(float red, float green, float blue, float alpha);
	private:
		static std::unique_ptr<RendererAPI> rendererAPI;
		static Renderer renderer;
		//void internalCameraUpdate(Camera& camera);
	};

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
		static std::unique_ptr<RendererAPI> create() {
			switch (currentAPI)
			{
				case API::None  : return nullptr;
				case API::OpenGL: return std::make_unique<OpenGLRenderer>();
			}

			return nullptr;
		}

		virtual int  init    ();
		virtual void drawMesh();
		virtual void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
		virtual void renderMesh (Mesh& mesh, Transform& transform);
		virtual void clear();

		virtual ~RendererAPI();

		static API get() { return currentAPI; };

	private:
		static API currentAPI;
	};
}