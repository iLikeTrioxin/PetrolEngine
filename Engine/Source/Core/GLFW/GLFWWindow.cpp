#include <PCH.h>

#include <utility>
#include "../Window/Window.h"
#include "GLFWWindow.h"
#include <Renderer/Renderer/Renderer.h>
// TODO: Remove unnecessary type size conversions

namespace PetrolEngine {

    GLFWWindow::GLFWWindow(int width, int height, const String& title) { LOG_FUNCTION();
        this->windowData = { width, height, title };
        this->window     = nullptr;
    }

    void GLFWWindow::showCursor(bool enabled) { LOG_FUNCTION();
        glfwSetInputMode(window, GLFW_CURSOR, enabled ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
    }

    void GLFWWindow::setVSync(bool enabled) { LOG_FUNCTION();
        glfwSwapInterval(enabled);
    }

    void GLFWWindow::setIcon(Image* image) { LOG_FUNCTION();
        GLFWimage icons[1];

        icons[0].pixels = image->getData  ();
        icons[0].height = image->getHeight();
        icons[0].width  = image->getWidth ();

        this->icon = image;

        glfwSetWindowIcon(window, 1, icons);
    }

    GLFWWindow::~GLFWWindow(){
        delete this->icon;
    }

    void GLFWWindow::createWindowSurface(void* i, const void* a, void* s){
//        glfwCreateWindowSurface(
//            *reinterpret_cast<VkInstance*>(i),
//            window,
//            reinterpret_cast<const VkAllocationCallbacks*>(a),
//            reinterpret_cast<      VkSurfaceKHR*         >(s)
//        );
    }
    void error_callback(int error, const char* msg) {
        std::string s;
        s = " [" + std::to_string(error) + "] " + msg + '\n';
        LOG(s,3);
        std::cerr << s << std::endl;
    }
    int GLFWWindow::init() { LOG_FUNCTION();
        int success = glfwInit();

        if (!success)
            return 0;

        glfwSetErrorCallback(error_callback);

        window = glfwCreateWindow(windowData.width, windowData.height, windowData.title.c_str(), nullptr, nullptr);

        if (!window) {
            LOG("Window failed to create" , 3);
            glfwTerminate();
            return 0;
        }

        glfwSetWindowUserPointer(window, &windowData);
        glfwSetWindowSizeCallback(window, [](GLFWwindow* windowPtr, int newWidth, int newHeight) {
                auto* newWindowData = reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(windowPtr));

                newWindowData->width  = newWidth ;
                newWindowData->height = newHeight;

                EventStack::addEvent( new WindowResizedEvent(*newWindowData) );
            }
        );

        glfwSetWindowCloseCallback(window, [](GLFWwindow* windowPtr) {
                WindowData& newWindowData = *(WindowData*)glfwGetWindowUserPointer(windowPtr);

                EventStack::addEvent(new WindowClosedEvent(newWindowData));
            }
        );

        glfwSetKeyCallback(window, [](GLFWwindow* windowPtr, int key, int scancode, int action, int mods) {
                switch (action) {
                    case GLFW_PRESS  : EventStack::addEvent(new KeyPressedEvent (key, false)); break;
                    case GLFW_REPEAT : EventStack::addEvent(new KeyPressedEvent (key, true )); break;
                    case GLFW_RELEASE: EventStack::addEvent(new KeyReleasedEvent(key       )); break;
                    default          :                                                         break;
                }
            }
        );

        glfwSetCharCallback(window, [](GLFWwindow* windowPtr, unsigned int keycode) {
                EventStack::addEvent( new KeyTypedEvent( (int) keycode) );
            }
        );

        // TODO: distinguish press and release events
        glfwSetMouseButtonCallback(window, [](GLFWwindow* windowPtr, int button, int action, int mods) {
                switch (action) {
                    case GLFW_PRESS  :
                    case GLFW_RELEASE: EventStack::addEvent( new MouseClickEvent(button) ); break;
                    default          :                                                      break;
                }
            }
        );

        glfwSetScrollCallback(window, [](GLFWwindow* windowPtr, double xOffset, double yOffset) {
                EventStack::addEvent( new MouseScrolledEvent(xOffset, yOffset) );
            }
        );

        glfwSetCursorPosCallback(window, [](GLFWwindow* windowPtr, double x, double y) {
                cursorXPos = x;
                cursorYPos = y;

                EventStack::addEvent( new MouseMovedEvent(x, y) );
            }
        );

        glfwMakeContextCurrent(window);

        if (Renderer::createGraphicsContext()->init((void*)glfwGetProcAddress))
            return -1;

        glfwSetTime( 0.0 );

        return 0;
    }
}