#pragma once

#include "window.h"
#include "device.h"
#include "swapchain.h"
#include "model.h"

#include <memory>
#include <vector>
#include <cassert>

namespace Engine
{
    class Renderer
    {
    public:
        static constexpr int WIDTH = 800;
        static constexpr int HEIGHT = 600;

        Renderer(Window &window, Device &device);
        ~Renderer();

        Renderer(const Renderer &) = delete;
        Renderer &operator=(const Renderer &) = delete;

        VkCommandBuffer beginFrame();
        void endFrame();

        void beginSwapChainRenderPass(VkCommandBuffer commandBuffer);
        void endSwapChainRenderPass(VkCommandBuffer commandBuffer);

        bool isFrameInProgress() const { return isFrameStarted; }

        VkCommandBuffer getCurrentCommandBuffer() const
        {
            assert(isFrameStarted && "Cannot get command buffer when frame not in progrss!");
            return commandBuffers[currentFrameIndex];
        }

        VkRenderPass getSwapChainRenderPass() const { return swapChain->getRenderPass(); }

        float getAspectRatio() const { return swapChain->extentAspectRatio(); }

        int getFrameIndex() const
        {
            assert(isFrameStarted && "Cannot get frames when frame not in progress!");

            return currentFrameIndex;
        }

    private:
        void createCommandBuffers();
        void freeCommandBuffers();
        void recreateSwapChain();

        Window &window;

        Device &device;

        std::unique_ptr<SwapChain> swapChain;

        std::vector<VkCommandBuffer> commandBuffers;

        uint32_t currentImageIndex;
        int currentFrameIndex{0};
        bool isFrameStarted{false};
    };
}