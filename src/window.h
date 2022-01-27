#pragma once

#define GLFW_INCLUDE_VULKAN // To include vulkan headers with glfw
#include <GLFW/glfw3.h>

#include <string>

namespace Engine
{
    class Window
    {
    public:
        Window(int w, int h, std::string name);
        ~Window();

        // We don't want to accidentally copy 2 windows and have 2 references. This is using RAII (Resource aqcuisition is initialization)
        Window(const Window &) = delete;
        Window &operator=(const Window &) = delete;

        bool shouldClose() { return glfwWindowShouldClose(window); }
        bool wasWindowResized() { return framebufferResized; }

        void resetWindowResizedFlag() { framebufferResized = false; }
        void createWindowSurface(VkInstance instance, VkSurfaceKHR *surface);

        GLFWwindow *getGLFWwindow() const { return window; }

        VkExtent2D getExtent() { return {static_cast<uint32_t>(width), static_cast<uint32_t>(height)}; }
    private:
        static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
        void initWindow();

        GLFWwindow *window;

        int width;
        int height;

        bool framebufferResized = false;

        std::string windowName;
    };
}