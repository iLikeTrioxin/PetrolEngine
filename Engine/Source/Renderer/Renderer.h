#pragma once

#include "RendererAPI.h"

namespace PetrolEngine {

    /*
     * Renderer class is just alias for functions from RendererAPI (like Renderer2D)
     */
	class Renderer {
	public:
	    static void init(RendererAPI::API targetAPI, bool debug = false);

	    // 2D stuff
	    static void renderText(const String& text, Transform& transform);
        static void drawSprite();

	    // 3D stuff
		static void renderMesh(Mesh& mesh, Transform& transform, Camera& camera);

		// utility stuff
		static void OnWindowResize        (uint32_t       width         , uint32_t height      );
		static void getDeviceConstantValue(DeviceConstant deviceConstant, void*    outputBuffer);
		static void clear();
		static void getErrors();
		static void setClearColor(float red, float green, float blue, float alpha);
	
	private:
		Renderer() = default;

	private:
	    static Ptr<RendererAPI> rendererAPI;
		static Renderer renderer;
	};
}
