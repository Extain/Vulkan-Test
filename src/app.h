#pragma once

#include "window.h"
#include "pipeline.h"
#include "device.h"
#include "gameObject.h"
#include "swapchain.h"
#include "model.h"

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
        void createPipelineLayout();
        void createPipeline();
        void createCommandBuffers();
        void freeCommandBuffers();
        void drawFrame();
        void recreateSwapChain();
        void recordCommandBuffer(int imageIndex);
        void renderGameObjects(VkCommandBuffer commandBuffer);

        Window window{WIDTH, HEIGHT, "Vulkan Test"};

        Device device{window};

        std::unique_ptr<SwapChain> swapChain;
        std::unique_ptr<Pipeline> pipeline;

        VkPipelineLayout pipelineLayout;
        std::vector<VkCommandBuffer> commandBuffers;
        std::vector<GameObject> gameObjects;
    };
}