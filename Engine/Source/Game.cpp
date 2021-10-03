#include <PCH.h>

#include "Game.h"
#include "Core/Files.h"
#include "Components.h"
#include "Entity.h"
#include "Renderer/Renderer.h"
#include "modelLoader.h"
#include "DebugTools.h"
#include "Renderer/Shader.h"
#include "Renderer/Text.h"

namespace PetrolEngine {
    Entity mainCamera = Entity();

    Game::Game() {
        //std::filesystem::current_path("C:/Users/2TPE/Desktop/PetrolEngine/build");
        DEBUG_LOG("Size of int8  is " << sizeof(int8 ));
        DEBUG_LOG("Size of int16 is " << sizeof(int16));
        DEBUG_LOG("Size of int32 is " << sizeof(int32));
        DEBUG_LOG("Size of int64 is " << sizeof(int64));

        this->window = Window::create(800, 500, "No hejka");

        Image::flipImages(true);

        window->init();
        //window->setIcon(Image("C:/Users/2TPE/Desktop/PetrolEngine/Engine/Resources/cobweb.png"));

        Renderer::init(RendererAPI::API::OpenGL);
        Text::init("../Engine/Resources/Fonts/Poppins/Poppins-Black.ttf");
        
        window->setVSync(false);
         
        auto basic = Shader::load(
            "default",
            ReadFile("../Engine/Resources/Shaders/shader.vert"),
            ReadFile("../Engine/Resources/Shaders/shader.frag")
        );

        basic->setInt  ("material.diffuse"  , 0  );
        basic->setInt  ("material.specular" , 0  );
        basic->setFloat("material.shininess", 1. );
        
        basic->setInt  ("light[0].lightType", 1  );
        basic->setVec3 ("light[0].direction", -1.0f, 0.0f, 1.0f);
        basic->setVec3 ("light[0].ambient"  , 0.2f, 0.2f, 0.2f);
        basic->setVec3 ("light[0].diffuse"  , glm::vec3(3.0f, 3.0f, 3.0f));
        basic->setVec3 ("light[0].specular" , 0.0f, 0.0f, 0.0f);

        modelLoader::Get().shader = basic;

        Scene& scene = scenes.emplace_back<>();

        mainCamera = scene.createEntity("Camera");
        
        auto a = modelLoader::Get().loadModel("../Engine/Resources/Models/Devildom girl/girl.fbx", &scene);
        auto b = modelLoader::Get().loadModel("../Engine/Resources/Models/Devildom girl/girl.fbx", &scene);
        
        auto& ka = b.getComponent<Transform>();
        ka.position.z -= 10;
        ka.rotation = glm::quat(glm::radians(glm::vec3(0.0f, 180.0f, 0.0f)));

        ExternalScript* s = new rotatee(&ka);
        b.addComponent<ExternalScript*>(s);

        //scenes[0].sceneRegistry.view<Transform>().each([&](Transform& trans) {
        //    trans.updateTransformMatrix();
        //    });

        //ka.rotation = glm::quat(glm::radians(glm::vec3(0, 180, 0)));
        //auto b = Entity(entt::null, &scenes[0]);

        //modelLoader::Get().loadModel("C:/Users/mpr19/source/repos/TechnoGamesCode/OwO/KAIO (C++)/KAIO (C++)/fbx/Devildom girl/d.fbx", &b);

        gameLoop();
    }

    void Game::gameLoop() { LOG_FUNCTION();
        uint   iter = 0;
        double time = 0;
        
        auto& camTra = mainCamera.getComponent<Transform>(       );
        auto& camera = mainCamera.addComponent<  Camera >(       );
        auto& camMov = mainCamera.addComponent< Movement>(&camTra);

        camera.updatePerspectiveMatrix(window->getAspectRatio());
        
        std::vector<double> deltaTimes;
        deltaTimes.reserve(100);

        struct sortDouble {
            bool operator()(double a, double b) const { return a < b; }
        };

        double dotOnePercentLow = 0.1;
        double    OnePercentLow = 0.1;
        double average          = 0.1;
        
        uint idk = 0;
        Renderer::getDeviceConstantValue(DeviceConstant::MAX_TEXTURE_IMAGE_UNITS, (void*) &idk);
        DEBUG_LOG("aaa:"<<std::to_string(idk));
        
        double prevoiusXCursorPos = cursorXPos;
        double prevoiusYCursorPos = cursorYPos;
        double previousFrame      = glfwGetTime();
        while (!window->shouldClose())
        {
            deltaXMousePos     = cursorXPos - prevoiusXCursorPos;
            deltaYMousePos     = cursorYPos - prevoiusYCursorPos;
            prevoiusXCursorPos = cursorXPos;
            prevoiusYCursorPos = cursorYPos;

            double currentFrame = glfwGetTime();
            deltaTime = currentFrame - previousFrame;
            previousFrame = currentFrame;

            uint32_t frameCount = deltaTimes.size();
            if (frameCount >= 100) {
                std::sort(deltaTimes.begin(), deltaTimes.end(), sortDouble());
                dotOnePercentLow = (deltaTimes.back() + dotOnePercentLow) * 0.5;

                double sum = 0.0;
                for (uint32_t i = 0; i < 10; i++) { sum += deltaTimes[frameCount - i - 1]; }
                OnePercentLow = (OnePercentLow + (sum * 0.1)) * 0.5;
                
                sum = 0.0;
                for (auto& e : deltaTimes) sum += e;

                average = sum * 0.01;

                deltaTimes.clear();
            }
            
            deltaTimes.push_back(deltaTime);

            previousFrame = glfwGetTime();

            LOG_SCOPE("Frame");
            Renderer::clear();

            if( window->isPressed(GLFW_KEY_ESCAPE) )
                window->close();
            
            if (window->isPressed(GLFW_KEY_R)) {
                auto shad1 = ReadFile("../Engine/Resources/Shaders/shader.vert");
                auto shad2 = ReadFile("../Engine/Resources/Shaders/shader.frag");

                Shader::load("default", "")->recompileShader(shad1.c_str(), shad2.c_str());
            }

            auto* wr = EventStack::getEvents<Window::WindowResizedEvent>();
            if (wr != nullptr) {
                for (auto w : *wr) {
                    camera.updatePerspectiveMatrix(window->getAspectRatio());
                    Renderer::OnWindowResize(w->data.width, w->data.height);
                }
            }

            camMov.update(window);
            for (int i = 0; i < scenes.size(); i++)
                scenes[i].update(window->getAspectRatio());

            // display frame rate
            {
                LOG_SCOPE("D-F-R");

                Transform a = Transform();

                //a.position = { 10.f, 475.f, 0.f };
                //Renderer::renderText(".1% LOW FPS: " + std::to_string(1.0 / dotOnePercentLow), a, camera, .4f);
                //
                //a.position = { 10.f, 450.f, 0.f };
                //Renderer::renderText("1.% LOW FPS: " + std::to_string(1.0 / OnePercentLow), a, camera, .4f);

                a.position = { 10.f, 425.f, 0.f };
                //Renderer2D::renderText( std::to_string(1.0 / average), a, camera, .4f);
            }

            EventStack::clear();
            
            window->swapBuffers();
            window->pollEvents ();
        }
    }
}