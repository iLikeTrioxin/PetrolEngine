#include "../../PCH.h"
#include "GLFWWindow.h"

#include "../../Renderer/GraphicsContext.h"

namespace Engine {

    int   GLFWWindow::init() {
        int success = glfwInit();

        if (!success)
            return 0;
        
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(windowData.width, windowData.height, windowData.title.c_str(), NULL, NULL);

        if (!window) {
            glfwTerminate();
            return 0;
        }

        if (GraphicsContext::create(window)->init(glfwGetProcAddress))
            return -1;
        
        glfwMakeContextCurrent   (window);
        glfwSetWindowUserPointer (window, &windowData);
        glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int Width, int Height) 
            {
                WindowData& windowData = *reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(window));
                
                windowData.width  = Width ;
                windowData.height = Height;
            });
        
        return 0;
    }
}