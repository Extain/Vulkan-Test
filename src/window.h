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
        void createWindowSurface(VkInstance instance, VkSurfaceKHR *surface);

        VkExtent2D getExtent() { return {static_cast<uint32_t>(width), static_cast<uint32_t>(height)}; }
    private:
        void initWindow();

        GLFWwindow *window;

        const int width;
        const int height;

        std::string windowName;
    };
}