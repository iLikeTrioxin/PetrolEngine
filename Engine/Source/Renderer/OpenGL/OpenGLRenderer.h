#pragma once

#include "../Renderer.h"

namespace Engine {
	
	class OpenGLRenderer : public RendererAPI {
	public:
		//static Shader&   loadShader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
		virtual void renderMesh  (Mesh& mesh, Transform& transform, Camera& camera) override;
		virtual void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		virtual void clear() override;
		virtual int  init() override;

		//static void updateCamera (Camera& camera);
		//void internalMeshRender  (Mesh& mesh, Transform& transform);
		//void internalCameraUpdate(Camera& camera);
		//Shader& internalLoadShader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
		void resetBuffers();
		//void internalGUI ();

	};
}
