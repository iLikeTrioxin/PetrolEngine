 #pragma once

#include <glad/glad.h>

#include "Renderer/RendererInterface/RendererI.h"

#include "OpenGLIndexBuffer.h"
#include "OpenGLShader.h"
#include "OpenGLTexture.h"
#include "OpenGLVertexArray.h"
#include "OpenGLVertexBuffer.h"

#include "Components/Transform.h"
#include "Components/Material.h"
#include "Components/Camera.h"

// TODO: make sure to move shader sources.

namespace PetrolEngine {
	
	class OpenGLRenderer : public RendererI {
	public:
		// 2D stuff
		void drawQuad2D(const Material& material, const Transform& transform) override;

		// 3D stuff
		void renderMesh(const Ref<VertexArrayI>& vao, const Transform& transform, const Material& material, const Camera* camera) override;

		// utility
		void setViewport(int x, int y, int width, int height) override;
		void clear() override;
		int  init (bool debug) override;
		void renderText(const String& text, const Transform& transform, const Material& material, const Camera* camera) override;

		void getDeviceConstantValue(DeviceConstant deviceConstant, void* outputBuffer) override;

		static void resetBuffers();

		const UnorderedMap<DeviceConstant, GLint> openGLDeviceConstants{
			{DeviceConstant::MAX_TEXTURE_IMAGE_UNITS, GL_MAX_TEXTURE_IMAGE_UNITS}
		};

        ~OpenGLRenderer() override = default;
	};
}
