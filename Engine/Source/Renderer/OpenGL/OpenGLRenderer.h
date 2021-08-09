#pragma once

#include "../Renderer.h"

namespace Engine {
	
	class OpenGLRenderer : public RendererAPI {
	public:
		//static Shader&   loadShader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
		virtual void renderMesh  (Mesh& mesh, Transform& transform, Camera& camera) override;
		virtual void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		virtual void clear() override;
		virtual void renderText(const std::string& text, Transform& transform, Camera& camera, float scale=1.f) override;
		virtual int  init() override;

		virtual void getDeviceConstantValue(DeviceConstant deviceConstant, void* outputBuffer) override;

		void resetBuffers();

		const std::unordered_map<DeviceConstant, GLint> OpenGLDeviceConstants{
			{DeviceConstant::MAX_TEXTURE_IMAGE_UNITS, GL_MAX_TEXTURE_IMAGE_UNITS}
		};
		//void internalGUI ();

	};
}
