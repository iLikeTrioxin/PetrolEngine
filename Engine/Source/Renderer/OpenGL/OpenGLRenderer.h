#pragma once

#include "../Renderer.h"

namespace Engine {
	
	class OpenGLRenderer : public RendererAPI {
	public:
		//static Shader&   loadShader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
		void renderMesh  (Mesh& mesh, Transform& transform) override;
		static void updateCamera (Camera& camera);
		void internalMeshRender  (Mesh& mesh, Transform& transform);
		void internalCameraUpdate(Camera& camera);
		Shader& internalLoadShader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
		void resetBuffers();
		void internalGUI ();

	};
}
