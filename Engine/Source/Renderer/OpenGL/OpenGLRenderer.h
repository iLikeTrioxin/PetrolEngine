 #pragma once

#include <glad/glad.h>

#include "../Renderer.h"
#include "../RendererResourceCreator.h"

#include "OpenGLIndexBuffer.h"
#include "OpenGLShader.h"
#include "OpenGLTexture.h"
#include "OpenGLVertexArray.h"
#include "OpenGLVertexBuffer.h"

// TODO: make sure to move shader sources.

namespace PetrolEngine {
	
	class OpenGLRenderer : public Renderer {
	public:
		// 2D stuff
		void drawQuad2D(Material material, Transform transform) override;

		// 3D stuff
		void renderMesh(Mesh& mesh, Transform& transform, Camera& camera) override;

		// utility
		void setViewport(int x, int y, int width, int height) override;
		void clear() override;
		int  init (bool debug) override;

		void getDeviceConstantValue(DeviceConstant deviceConstant, void* outputBuffer) override;

		static void resetBuffers();

		const UnorderedMap<DeviceConstant, GLint> openGLDeviceConstants{
			{DeviceConstant::MAX_TEXTURE_IMAGE_UNITS, GL_MAX_TEXTURE_IMAGE_UNITS}
		};
	};
}
