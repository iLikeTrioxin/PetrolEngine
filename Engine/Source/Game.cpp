#include "PCH.h"
#include "Game.h"
#include "Core/Files.h"
#include "Components.h"
#include "Entity.h"
#include "Renderer/Renderer.h"
#include "modelLoader.h"
#include "DebugTools.h"
#include "Renderer/Shader.h"

namespace Engine {

    Entity mainCamera = Entity();

    Game::Game() {
        this->window = Window::create(600, 250, "No hejka");

        window->init();
        Renderer::init();
        
        glfwSwapInterval(0);

        auto basic = Shader::load(
            "default",
            ReadFile("../Engine/Resources/Shaders/shader.vert"),
            ReadFile("../Engine/Resources/Shaders/shader.frag")
        );

        basic->setInt  ("material.diffuse"  , 0  );
        basic->setInt  ("material.specular" , 0  );
        basic->setFloat("material.shininess", 1. );
        basic->setFloat("light[1].lightType", 0  );
        basic->setFloat("light[2].lightType", 0  );
        basic->setFloat("light[3].lightType", 0  );
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
        
        //scenes[0].sceneRegistry.view<Transform>().each([&](Transform& trans) {
        //    trans.updateTransformMatrix();
        //    });

        //ka.rotation = glm::quat(glm::radians(glm::vec3(0, 180, 0)));
        //auto b = Entity(entt::null, &scenes[0]);

        //modelLoader::Get().loadModel("C:/Users/mpr19/source/repos/TechnoGamesCode/OwO/KAIO (C++)/KAIO (C++)/fbx/Devildom girl/d.fbx", &b);

        gameLoop();
    }

    void Game::gameLoop() {
        LOG_FUNCTION();

        uint   iter = 0;
        double time = 0;
        
        auto& camTra = mainCamera.getComponent<Transform>();
        auto& camera = mainCamera.addComponent<Camera>();
        auto& camMov = mainCamera.addComponent<Movement>(&camTra);

        camera.updatePerspectiveMatrix(window->getAspectRatio());
        
        double prevoiusXCursorPos = cursorXPos;
        double prevoiusYCursorPos = cursorYPos;
        double previousFrame      = glfwGetTime();
        while (!window->shouldClose())
        {
            LOG_SCOPE("Frame");
            Renderer::clear();

            if( window->isPressed(GLFW_KEY_ESCAPE) )
                window->close();

            deltaXMousePos     = cursorXPos - prevoiusXCursorPos;
            deltaYMousePos     = cursorYPos - prevoiusYCursorPos;
            prevoiusXCursorPos = cursorXPos;
            prevoiusYCursorPos = cursorYPos;

            double currentFrame = glfwGetTime();
            deltaTime           = currentFrame - previousFrame;
            previousFrame       = currentFrame;

            if (iter >= 100) {
                std::cout<<(time / iter)<<std::endl;
                time = 0;
                iter = 0;
            }

            time += deltaTime;
            iter += 1;

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


            window->swapBuffers();
            window->pollEvents ();
        }
    }
}