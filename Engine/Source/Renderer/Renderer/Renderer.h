#pragma once

#include "Aliases.h"

#include <memory>

#include "DebugTools.h"

#include "Components/Transform.h"
#include "Components/Mesh.h"
#include "Components/Camera.h"

#include "Text.h"

#include "Renderer/RendererInterface/RendererResourceCreator.h"

// abstract classes
#include "../RendererInterface/Framebuffer.h"

#include "Core/Files.h"

namespace PetrolEngine {

    struct RendererResources{
        UnorderedMap<String, Ref<Shader>> shaders;
        UnorderedMap<String, Ref<Texture>> fonts;
    };

    class Renderer {
    public:
        static UnorderedMap<RRC*, RendererResources*> rendererResourcesCache;
        static  RendererResources* rendererResources;

        static void setContext(RRC& context){
            creator = &context;
            renderer = creator->newRenderer();
            auto x = rendererResourcesCache.find(creator);

            if(x == rendererResourcesCache.end())
                rendererResourcesCache[creator] = new RendererResources();

            rendererResources = rendererResourcesCache[creator];
        }


        // framebuffer
        static     Framebuffer*    newFramebuffer(const FramebufferSpecification& spec) { return         creator->newFramebuffer(spec) ; }
        static Ref<Framebuffer> createFramebuffer(const FramebufferSpecification& spec) { return Ref<Framebuffer>(newFramebuffer(spec)); }

        // texture
        static Texture* newTexture(const Image* image) { return creator->newTexture(image); }
        static Texture* newTexture(int width, int height, TextureFormat format, TextureType type = TextureType::Texture2D) { return creator->newTexture(width, height, format, type); }

        static Ref<Texture> createTexture(const Image* image){ return Ref<Texture>(newTexture(image)); }
        static Ref<Texture> createTexture(int width, int height, TextureFormat format, TextureType type = TextureType::Texture2D){ return Ref<Texture>(newTexture(width, height, format, type)); }

        // Vertex array
        static     VertexArray*    newVertexArray() { return         creator->newVertexArray() ; }
        static Ref<VertexArray> createVertexArray() { return Ref<VertexArray>(newVertexArray()); }

        // Vertex buffer
        static     VertexBuffer*    newVertexBuffer(VertexLayout layout) { return          creator->newVertexBuffer(layout) ; }
        static Ref<VertexBuffer> createVertexBuffer(VertexLayout layout) { return Ref<VertexBuffer>(newVertexBuffer(layout)); }

        static     VertexBuffer*    newVertexBuffer(VertexLayout layout, const void* data, int64 size) { return          creator->newVertexBuffer(layout, data, size) ; }
        static Ref<VertexBuffer> createVertexBuffer(VertexLayout layout, const void* data, int64 size) { return Ref<VertexBuffer>(newVertexBuffer(layout, data, size)); }

        // index buffer
        static     IndexBuffer*    newIndexBuffer(const void* data, int64 size) { return         creator->newIndexBuffer(data, size) ; }
        static Ref<IndexBuffer> createIndexBuffer(const void* data, int64 size) { return Ref<IndexBuffer>(newIndexBuffer(data, size)); }

        static     IndexBuffer*    newIndexBuffer() { return         creator->newIndexBuffer() ; }
        static Ref<IndexBuffer> createIndexBuffer() { return Ref<IndexBuffer>(newIndexBuffer()); }

        // graphics context
        static     GraphicsContext*    newGraphicsContext(){ return             creator->newGraphicsContext() ; }
        static Ref<GraphicsContext> createGraphicsContext(){ return Ref<GraphicsContext>(newGraphicsContext()); }

        // shader
        static Shader* newShader(const String&           name,
                                 const String&   vertexShader,
                                 const String& fragmentShader,
                                 const String& geometryShader  ) {
            return creator->newShader(name, vertexShader, fragmentShader, geometryShader);
        }
        static Ref<Shader> createShader(const String&        name,
                                        const String&   vertexSrc,
                                        const String& fragmentSrc,
                                        const String& geometrySrc ){
            return Ref<Shader>(newShader(name, vertexSrc, fragmentSrc, geometrySrc));
        }


        static Ref<Shader> loadShader(const String& filePath);
        static Ref<Shader> loadShader(const String& name       ,
                                      const String& vertexSrc  ,
                                      const String& fragmentSrc,
                                      const String& geometrySrc = "" );

        static int  init    (bool debug) { return renderer->init(debug); };
        static void setViewport(int x, int y, int width, int height) { return renderer->setViewport(x, y, width, height); };
        static void renderMesh (Mesh& mesh, Transform& transform) {
            auto vao = mesh.getVertexArray();
            Vector<const Texture*> textures;

            textures.reserve(mesh.material.textures.size());
            for(auto& texture : mesh.material.textures)
                textures.push_back(texture.get());

            return renderer->renderMesh(vao.get(), transform, textures, mesh.material.shader.get(), camera);
        }

        static void renderText(const String& text, const Transform& transform, const String& font) {
            Material fontMaterial;
            Text::FontAtlas* atlas = &Text::getAtlas(font);

            auto texture = rendererResources->fonts.find(font);

            if(texture == rendererResources->fonts.end()){
                rendererResources->fonts[font] = Renderer::createTexture(
                        atlas->atlas->getWidth(),
                        atlas->atlas->getHeight(),
                        TextureFormat::RED,
                        TextureType::Texture2D
                );

                rendererResources->fonts[font]->updateTextureImage(atlas->atlas->getData());
            }

            auto shader = Renderer::loadShader( "textShader",
                    ReadFile("../Hei/Resources/Shaders/textShader.vert"),
                    ReadFile("../Hei/Resources/Shaders/textShader.frag")
            );

            return renderer->renderText(text, transform, rendererResources->fonts[font].get(), atlas, shader.get(), camera);
        };

        static void clear() { return renderer->clear(); };
        static void getDeviceConstantValue(DeviceConstant deviceConstant, void* outputBuffer) { return renderer->getDeviceConstantValue(deviceConstant, outputBuffer); };
        static void renderFramebuffer(const Ref<Framebuffer> framebuffer, const Ref<Shader> shader) {
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
        static RendererAPI* renderer;
        static RRC* creator;
    };
}
