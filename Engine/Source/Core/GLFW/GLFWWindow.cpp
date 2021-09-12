#include "../../PCH.h"
#include "GLFWWindow.h"

#include "../../Renderer/GraphicsContext.h"

namespace Engine {

    GLFWWindow::GLFWWindow(uint32_t width, uint32_t height, std::string title) { LOG_FUNCTION();
        this->windowData = { width, height, title };
        this->window     = nullptr;
    }


    void GLFWWindow::setVSync(bool enabled) { LOG_FUNCTION();
        glfwSwapInterval(enabled);
    }

    void GLFWWindow::setIcon(Image image) { LOG_FUNCTION();
        GLFWimage icons[1];
        
        icons[0].pixels = image.getData();

        glfwSetWindowIcon(window, 1, icons);
    }

    void GLFWWindow::createWindowSurface(void* i, const void* a, void* s){
        glfwCreateWindowSurface(
            *reinterpret_cast<VkInstance*>(i),
            window,
            reinterpret_cast<const VkAllocationCallbacks*>(a),
            reinterpret_cast<      VkSurfaceKHR*         >(s)
        );
    }

    int GLFWWindow::init() { LOG_FUNCTION();
        int success = glfwInit();

        if (!success)
            return 0;

        //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        //glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
        window = glfwCreateWindow(windowData.width, windowData.height, windowData.title.c_str(), nullptr, nullptr);

        if (!window) {
            debug_log("window failed to create");
            glfwTerminate();
            return 0;
        }

        if (GraphicsContext::create(window)->init((void*) glfwGetProcAddress))
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
                case GLFW_PRESS  : EventStack::addEvent(new KeyPressedEvent (key, false)); break;
                case GLFW_REPEAT : EventStack::addEvent(new KeyPressedEvent (key, true )); break;
                case GLFW_RELEASE: EventStack::addEvent(new KeyReleasedEvent(key       )); break;
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

        //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwMakeContextCurrent(window);
        return 0;
    }
}