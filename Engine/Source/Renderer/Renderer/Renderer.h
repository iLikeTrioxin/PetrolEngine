#pragma once

#include "Aliases.h"

#include <memory>

#include "DebugTools.h"

#include "Components/Transform.h"
#include "Components/Mesh.h"
#include "Components/Camera.h"

#include "Text.h"
#include "Shader.h"
#include "Texture.h"

#include "Renderer/RendererInterface/RendererResourceCreator.h"

#include "Core/Files.h"

namespace PetrolEngine {

    class Renderer {
    public:
        static void setContext(RRC& context){
            creator = &context;
            renderer = creator->newRenderer();
        }

        static int  init    (bool debug) { return renderer->init(debug); };
        static void setViewport(int x, int y, int width, int height) { return renderer->setViewport(x, y, width, height); };
        static void renderMesh (Mesh& mesh, Transform& transform) {
            return renderer->renderMesh(mesh.vertexArray, transform, mesh.material, camera);
        }

        static void renderText(const String& text, const Transform& transform, const String& font) {
            Material fontMaterial;
            Image* atlas = Image::create(
                Text::getAtlas(font).atlas->getData(),
                Text::getAtlas(font).atlas->getWidth(),
                Text::getAtlas(font).atlas->getHeight(),
                8,
                1,
                0
            );

            String vertexShaderSource   = ReadFile("../Hei/Resources/Shaders/textShader.vert");
            String fragmentShaderSource = ReadFile("../Hei/Resources/Shaders/textShader.frag");

            auto shader = Shader::load(
                    "textShader",
                    vertexShaderSource.c_str(),
                    fragmentShaderSource.c_str(),
                    nullptr
            );

            fontMaterial.shader = shader;
            fontMaterial.textures.push_back(Texture::create(atlas));

            //delete atlas;

            return renderer->renderText(text, transform, fontMaterial, camera);
        };

        static void clear() { return renderer->clear(); };
        static void getDeviceConstantValue(DeviceConstant deviceConstant, void* outputBuffer) { return renderer->getDeviceConstantValue(deviceConstant, outputBuffer); };
        static void renderFramebuffer(const Ref<FramebufferI> framebuffer, const Ref<ShaderI> shader) {
            const Vector<Vertex> planeVertices = {
                    // pos        // tex
                    Vertex({-1.0f, -1.0f, 0.0f}, {0.0f, 0.0f}),
                    Vertex({ 1.0f,  1.0f, 0.0f}, {1.0f, 1.0f}),
                    Vertex({-1.0f,  1.0f, 0.0f}, {0.0f, 1.0f}),

                    Vertex({-1.0f, -1.0f, 0.0f}, {0.0f, 0.0f}),
                    Vertex({ 1.0f, -1.0f, 0.0f}, {1.0f, 0.0f}),
                    Vertex({ 1.0f,  1.0f, 0.0f}, {1.0f, 1.0f})
            };
        };
        static void setCamera(const Camera* cam) { camera = cam; }
        // static void drawQuad2D(Material material, Transform transform) { return renderer->drawQuad2D(material, transform); };

        ~Renderer() = default;

        static RRC* getCreator() { return creator; }

    private:
        static const Camera* camera;
        static RendererI* renderer;
        static RRC* creator;
    };
}

#define CREATE_RENDERER_RESOURCE_CREATOR(type)                                     \
    class type {                                                                   \
    public:                                                                        \
        template<typename ... Args>                                                \
        static Ref<type##I> create(Args... args) {                                     \
            return Ref<type##I>(Renderer::getCreator()->new##type(std::forward<Args>(args)...)); \
        }                                                                          \
    };
