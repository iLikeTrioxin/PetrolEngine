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

	class: public RendererResourceCreator {
		VertexBuffer* newVertexBuffer(const VertexLayout& layout, const void* data, int64 size) override { return new OpenGLVertexBuffer(layout, data, size); };
		IndexBuffer * newIndexBuffer (                            const void* data, int64 size) override { return new OpenGLIndexBuffer (        data, size); };
		VertexArray * newVertexArray (                                                        ) override { return new OpenGLVertexArray (                  ); };
		Renderer    * newRenderer    (                                                        ) override { return new OpenGLRenderer    (                  ); };

		Shader      * newShader      ( String&& vertexShader  ,
					                   String&& fragmentShader,
		                               String&& geometryShader  ) override { return new OpenGLShader(vertexShader, fragmentShader, geometryShader); };
	} OpenGL;
}
