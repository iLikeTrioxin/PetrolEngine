#include "../../PCH.h"
#include "GLFWWindow.h"

#include "../../Renderer/GraphicsContext.h"

namespace Engine {

    GLFWWindow::GLFWWindow(uint32_t width, uint32_t height, std::string title) {
        this->windowData = { width, height, title };
    }

    int GLFWWindow::init() {
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
        
        glfwMakeContextCurrent  (window);
        glfwSetWindowUserPointer(window, &windowData);
        
        glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int Width, int Height) {
                WindowData& windowData = *reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(window));
                
                windowData.width  = Width ;
                windowData.height = Height;
                
                EventStack::addEvent( new WindowResizedEvent(windowData) );
            }
        );

        glfwSetWindowCloseCallback(window, [](GLFWwindow* window) {
                WindowData& windowData = *(WindowData*)glfwGetWindowUserPointer(window);

                EventStack::addEvent(new WindowClosedEvent(windowData));
            }
        );

        glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
                switch (action) {
                    case GLFW_PRESS  : EventStack::addEvent(new KeyPressedEvent (key)); break;
                    case GLFW_RELEASE: EventStack::addEvent(new KeyReleasedEvent(key)); break;
                    case GLFW_REPEAT : EventStack::addEvent(new KeyHoldenEvent  (key)); break;
                }
            }
        );

        glfwSetCharCallback(window, [](GLFWwindow* window, unsigned int keycode) {
                EventStack::addEvent( new KeyTypedEvent(keycode) );
            }
        );

        glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
                switch (action)
                {
                    case GLFW_PRESS  : EventStack::addEvent( new MouseClickEvent(button) ); break;
                    case GLFW_RELEASE: EventStack::addEvent( new MouseClickEvent(button) ); break;
                }
            }
        );

        glfwSetScrollCallback(window, [](GLFWwindow* window, double xOffset, double yOffset) {
                EventStack::addEvent( new MouseScrolledEvent(xOffset, yOffset) );
            }
        );

        glfwSetCursorPosCallback(window, [](GLFWwindow* window, double x, double y) {
                cursorXPos = x;
                cursorYPos = y;

                EventStack::addEvent( new MouseMovedEvent(x, y) );
            }
        );

        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        return 0;
    }
}