#include "window.h"

#include <stdexcept>

namespace Engine
{
    Window::Window(int w, int h, std::string name) : width{w}, height{h}, windowName{name}
    {
        initWindow();
    }

    Window::~Window()
    {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void Window::initWindow()
    {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

        window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
        
        // Allows us to pair a glfw window object with an arbitrary pointer value, which is the window object.
        glfwSetWindowUserPointer(window, this);
        // Whenever the window is resized call the framebufferResizeCallback
        glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
    }

    void Window::createWindowSurface(VkInstance instance, VkSurfaceKHR *surface)
    {
        if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create window surface!");
        }
    }

    void Window::framebufferResizeCallback(GLFWwindow *window, int width, int height)
    {
        auto tempWindow = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
        tempWindow->framebufferResized = true;
        tempWindow->width = width;
        tempWindow->height = height;
    }
}