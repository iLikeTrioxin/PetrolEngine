 #pragma once

#include <glad/glad.h>

#include "Renderer/RendererInterface/RendererI.h"

#include "MetalIndexBuffer.h"
#include "MetalShader.h"
#include "MetalTexture.h"
#include "MetalVertexArray.h"
#include "MetalVertexBuffer.h"

#include "Components/Transform.h"
#include "Components/Material.h"
#include "Components/Camera.h"
#include <Renderer/Renderer/Text.h>
// TODO: make sure to move shader sources.

namespace PetrolEngine {
	
	class MetalRenderer : public RendererAPI {
	public:
		// 2D stuff
		void drawQuad2D(const Texture* texture, const Transform* transform, Shader* shader, const Camera* camera, glm::vec4 texCoords = {0,0,1,1}) override;

		// 3D stuff
		void renderMesh(const VertexArray* vao, const Transform& transform, const Vector<const Texture*>& textures, Shader* shader, const Camera* camera) override;

		// utility
		void setViewport(int x, int y, int width, int height) override;
		void clear() override;
		int  init (bool debug) override;
		void renderText(const String& text, const Transform& tran, const Texture* atlas, Text::FontAtlas* fa, Shader* shader, const Camera* cam) override;

		void getDeviceConstantValue(DeviceConstant deviceConstant, void* outputBuffer) override;

		static void resetBuffers();

		const UnorderedMap<DeviceConstant, GLint> MetalDeviceConstants{
			{DeviceConstant::MAX_TEXTURE_IMAGE_UNITS, GL_MAX_TEXTURE_IMAGE_UNITS}
		};

        ~MetalRenderer() override = default;

        void drawQuad2D(const Material &material, const Transform &transform, const Camera *camera);
    };
}
