#pragma once

#include "../Renderer.h"

#include <glad/glad.h>

namespace PetrolEngine {
	
	class OpenGLRenderer : public RendererAPI {
	public:
		// 2D stuff
	    void renderText(const String& text, Transform& transform) override;

		// 3D stuff
		void renderMesh(Mesh& mesh, Transform& transform, Camera& camera) override;

		// utility
		void setViewport(int x, int y, int width, int height) override;
		void clear() override;
		int  init (bool debug) override;

		void getDeviceConstantValue(DeviceConstant deviceConstant, void* outputBuffer) override;

		static void resetBuffers();

		const std::unordered_map<DeviceConstant, GLint> openGLDeviceConstants{
			{DeviceConstant::MAX_TEXTURE_IMAGE_UNITS, GL_MAX_TEXTURE_IMAGE_UNITS}
		};
	};
}
