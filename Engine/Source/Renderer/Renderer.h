#pragma once

#include <memory>
#include "../Components.h"
#include "../DebugTools.h"

namespace Engine {

	enum class DeviceConstant {
		None,

		// Compute
		MAX_COMPUTE_SHADER_STORAGE_BLOCKS,
		MAX_COMPUTE_TEXTURE_IMAGE_UNITS,
		MAX_COMPUTE_UNIFORM_BLOCKS,
		MAX_COMPUTE_UNIFORM_COMPONENTS,
		MAX_COMPUTE_ATOMIC_COUNTERS,
		MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS,
		MAX_COMPUTE_WORK_GROUP_INVOCATIONS,
		MAX_COMPUTE_WORK_GROUP_COUNT,
		MAX_COMPUTE_WORK_GROUP_SIZE,
		MAX_COMBINED_SHADER_STORAGE_BLOCKS,
		MAX_COMBINED_COMPUTE_UNIFORM_COMPONENTS,

		// Texture related
		MAX_TEXTURE_IMAGE_UNITS,
		MAX_3D_TEXTURE_SIZE,
		MAX_TEXTURE_SIZE,
		MAX_ARRAY_TEXTURE_LAYERS,
		MAX_CLIP_DISTANCES,
		MAX_COLOR_TEXTURE_SAMPLES,

		// Shader related
		MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS,
		MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS,
		MAX_COMBINED_TEXTURE_IMAGE_UNITS,
		MAX_COMBINED_UNIFORM_BLOCKS,
		MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS,
		MAX_CUBE_MAP_TEXTURE_SIZE,
		MAX_DEPTH_TEXTURE_SAMPLES,

		// Buffer related
		MAX_ELEMENTS_INDICES,
		MAX_ELEMENTS_VERTICES,

		// Framebuffer
		MAX_FRAMEBUFFER_WIDTH,
		MAX_FRAMEBUFFER_HEIGHT,
		MAX_FRAMEBUFFER_LAYERS,
		MAX_FRAMEBUFFER_SAMPLES,

		// Others
		MAX_SERVER_WAIT_TIMEOUT,
		MAX_TEXTURE_BUFFER_SIZE,
		MAX_VIEWPORTS,
		MAX_DRAW_BUFFERS,
		MAX_DUAL_SOURCE_DRAW_BUFFERS
	};

	/// <summary>
	/// Graphics API interface for Renderer.
	/// It cannot be integrated with Renderer becouse it's functions are static.
	/// </summary>
	class RendererAPI {
	public:
		enum class API {
			None   = 0,

			OpenGL = 1
		};

	public:
		static std::unique_ptr<RendererAPI> create();
		
		virtual int  init    () = 0;
		virtual void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void renderMesh (Mesh& mesh, Transform& transform, Camera& camera) = 0;
		virtual void renderText(const std::string& text, Transform& transform, Camera& camera, float scale = 1.f) = 0;
		virtual void clear() = 0;
		virtual void getDeviceConstantValue(DeviceConstant deviceConstant, void* outputBuffer) = 0;

		virtual ~RendererAPI() = default;

		static API get() { return currentAPI; };

	private:
		static API currentAPI;
	};

	class Renderer {
	public:
		static int       init() { return rendererAPI->init(); };
		static void renderText(const std::string& text, Transform& transform, Camera& camera, float scale = 1.f) { LOG_FUNCTION(); rendererAPI->renderText(text, transform, camera, scale); }
		//static Shader&   loadShader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
		static void renderMesh(Mesh& mesh, Transform& transform, Camera& camera) { LOG_FUNCTION(); rendererAPI->renderMesh(mesh, transform, camera); };
		static void OnWindowResize(uint32_t width, uint32_t   height) { LOG_FUNCTION(); rendererAPI->setViewport(0, 0, width, height); };
		
		static void getDeviceConstantValue(DeviceConstant deviceConstant, void* outputBuffer) { LOG_FUNCTION(); rendererAPI->getDeviceConstantValue(deviceConstant, outputBuffer); };
		static void clear() { LOG_FUNCTION(); rendererAPI->clear(); }
		static void getErrors();
		static void setClearColor(float red, float green, float blue, float alpha);
	
	private:
		Renderer() { rendererAPI = RendererAPI::create(); }
		static Renderer& get () { return renderer; };

	private:
		static std::unique_ptr<RendererAPI> rendererAPI;
		static Renderer renderer;
	};
}
