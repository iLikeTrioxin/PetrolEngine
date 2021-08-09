#include <iostream>
#include "Game.h"

int main()
{
    Engine::Game a = Engine::Game();
    return 0;
}

/*
#include <iostream>
#include <cassert>
#include <vector>
class Renderer {
public:
    static int getRenderer() {
        
    }

    RendererAPI* rendererAPI;
    static std::vector<RendererResource> rendererResources;
};

template<typename T>
class RendererResource {
public:
    static std::vector<RendererResource> resources;
};

class RendererAPI {
public:

};

class OpenGLRenderer : public RendererAPI {
public:

};

class VulcanRenderer : public RendererAPI {
public:

};

template<typename ... T>
class TextureInterface: T {

};

class Texture : TextureInterface<OpenGLTexture, VulcanTexture> {
public:

};

class OpenGLTexture : Texture {
public:

};

class VulcanTexture : Texture {
public:

};

int main(int argc, char* argv[])
{
    
    // syntax i wish
    
    Renderer::renderMesh(mesh, transform, camera);
    
    auto tex1 = texture::create("fgdg");

    Renderer::switchAPI<OpenGLRenderer>();
    

    return 0;
}
*/