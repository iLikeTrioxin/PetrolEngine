#include "PrecompiledHeader.h"
#include "Window.h"

int WIDTH;
int HEIGHT;

void  framebuffer_size_callback(GLFWwindow* window, int Width, int Height)
{
    WIDTH  = Width;
    HEIGHT = Height;
    glViewport(0, 0, Width, Height);
}
namespace Engine {
    Window::Window() {
        createWindowAndContent();
    }
    int   Window::createWindowAndContent() {
        if (!glfwInit())
            return -1;

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        windowHandle = glfwCreateWindow(WIDTH, HEIGHT, "Hello World", NULL, NULL);

        if (!windowHandle)
        {
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(windowHandle);
        glfwSetFramebufferSizeCallback(windowHandle, framebuffer_size_callback);

        return 0;
    }
    void  Window::getActualWindowSize() {
        glfwGetWindowSize(windowHandle, &WIDTH, &HEIGHT);
    }
    float Window::getAspectRatio() {
        return (float)WIDTH / HEIGHT;
    }
}