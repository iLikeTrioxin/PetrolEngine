#include "PCH.h"
#include "Game.h"

#include "Components.h"
#include "Entity.h"
#include "Renderer.h"
#include "modelLoader.h"
#include "DebugTools.h"

namespace Engine {

    double deltaXMousePos = 0.0;
    double deltaYMousePos = 0.0;
    double cursorXPos     = 0.0;
    double cursorYPos     = 0.0;
    double deltaTime      = 0.0;
    
    Entity mainCamera = Entity();

    void mouse_callback(GLFWwindow* _window, double xpos, double ypos) {
        cursorXPos     = xpos;
        cursorYPos     = ypos;
    }

    int Game::initalizeGLEW() {
        if (!gladLoadGL())
            return 1;
        
        initalizeTextureSettings(true);

        glEnable  (   GL_DEPTH_TEST   );
        glEnable  (GL_DEPTH_BUFFER_BIT);
        glEnable  (    GL_CULL_FACE   );
        glCullFace(      GL_BACK      );

        glfwSwapInterval(0);
        
        return 0;
    }

    Game::Game() {
        if (initalizeGLEW())
            debug_log("[!] Error while initalizing GLEW.");

        Renderer::get().parentWindow = &window;

        Shader& basic = Renderer::loadShader("C:/Users/mpr19/Desktop/Engine/Engine/Resources/Shaders/shader.vert", "C:/Users/mpr19/Desktop/Engine/Engine/Resources/Shaders/shader.frag");
        basic.setInt("material.diffuse", 0);
        basic.setInt("material.specular", 0);
        basic.setFloat("material.shininess", 1.0f);
        basic.setInt("light[0].lightType", 1);
        basic.setVec3("light[0].direction", -1.0f, 0.0f, 1.0f);
        basic.setVec3("light[0].ambient", 0.2f, 0.2f, 0.2f);
        basic.setVec3("light[0].diffuse", glm::vec3(3.0f, 3.0f, 3.0f));
        basic.setVec3("light[0].specular", 0.0f, 0.0f, 0.0f);
        basic.setFloat("light[1].lightType", 0);
        basic.setFloat("light[2].lightType", 0);
        basic.setFloat("light[3].lightType", 0);

        modelLoader::Get().shader = &basic;

        Scene& scene = scenes.emplace_back<>();

        mainCamera = scene.createEntity("Camera");
        
        auto a = modelLoader::Get().loadModel("C:/Users/mpr19/Desktop/Engine/Engine/Resources/Models/Devildom girl/blender/exports/devilgurl.fbx", &scene);
        auto b = modelLoader::Get().loadModel("C:/Users/mpr19/Desktop/Engine/Engine/Resources/Models/Devildom girl/blender/exports/devilgurl.fbx", &scene);
        
        auto& ka = b.getComponent<Transform>();
        ka.position.z -= 10;
        ka.rotation = glm::quat(glm::radians(glm::vec3(0.0f, 180.0f, 0.0f)));
        
        //scenes[0].sceneRegistry.view<Transform>().each([&](Transform& trans) {
        //    trans.updateTransformMatrix();
        //    });

        //ka.rotation = glm::quat(glm::radians(glm::vec3(0, 180, 0)));
        //auto b = Entity(entt::null, &scenes[0]);

        //modelLoader::Get().loadModel("C:\\Users\\mpr19\\source\\repos\\TechnoGamesCode\\OwO\\KAIO (C++)\\KAIO (C++)\\fbx\\Devildom girl\\d.fbx", &b);
        glfwSetCursorPosCallback(window.windowHandle, mouse_callback);
        glfwSetInputMode(window.windowHandle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        gameLoop();
    }

    void Game::gameLoop() {
        LOG_FUNCTION();

        uint   iter = 0;
        double time = 0;
        
        auto& camTra = mainCamera.getComponent<Transform>();
        auto& camera = mainCamera.addComponent<Camera>();
        auto& camMov = mainCamera.addComponent<Movement>(&camTra);

        double prevoiusXCursorPos = cursorXPos;
        double prevoiusYCursorPos = cursorYPos;
        double previousFrame      = glfwGetTime();
        while (!glfwWindowShouldClose(window.windowHandle))
        {
            LOG_SCOPE("Frame");
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            if (glfwGetKey(window.windowHandle, GLFW_KEY_ESCAPE))
                glfwSetWindowShouldClose(window.windowHandle, true);

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

            camMov.update();

            for (int i = 0; i < scenes.size(); i++)
                scenes[i].update();


            glfwSwapBuffers(window.windowHandle);
            
            glfwPollEvents();

        }
    }
}