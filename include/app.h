#pragma once

#include "window.h"
#include "device.h"
#include "gameObject.h"
#include "model.h"
#include "renderer.h"
#include "descriptors.h"

#include <memory>
#include <vector>

namespace Engine
{
    class App
    {
    public:
        static constexpr int WIDTH = 800;
        static constexpr int HEIGHT = 600;

        App();
        ~App();

        App(const App &) = delete;
        App &operator=(const App &) = delete;

        void run();

    private:
        void loadGameObjects();

        Window window{WIDTH, HEIGHT, "Vulkan Test"};
        Device device{window};

        Renderer renderer{window, device};

        std::unique_ptr<DescriptorPool> globalPool{};

        std::vector<GameObject> gameObjects;

        const float MAX_FRAME_TIME = 0.4f;
    };
}