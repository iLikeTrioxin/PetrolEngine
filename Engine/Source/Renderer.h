#pragma once

namespace Engine {

	class Transform;
	class Camera;
	class Window;
	class Mesh;

	class Renderer {
	public:
		Window* parentWindow;
		Renderer(const Renderer&) = delete;

		
		static Renderer& get      ();
		static Window*   getWindow();
		static Shader&   loadShader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
		static void renderMesh  (Mesh& mesh, Transform& transform);
		static void updateCamera(Camera& camera);
	private:
		std::vector<Shader> loadedShaders;
		uint currentShader = NULL;
		static Renderer rendererInstance;
		Renderer();
		~Renderer();
		void internalMeshRender  (Mesh& mesh, Transform& transform);
		void internalCameraUpdate(Camera& camera);
		Shader& internalLoadShader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
		void resetBuffers();
		void internalGUI ();

	};
}