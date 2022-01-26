#pragma once

#include "pipeline.h"
#include "device.h"
#include "gameObject.h"
#include "camera.h"

#include <memory>
#include <vector>

namespace Engine
{
    class SimpleRenderSystem
    {
    public:
        SimpleRenderSystem(Device &device, VkRenderPass renderPass);
        ~SimpleRenderSystem();

        SimpleRenderSystem(const SimpleRenderSystem &) = delete;
        SimpleRenderSystem &operator=(const SimpleRenderSystem &) = delete;

        void renderGameObjects(VkCommandBuffer commandBuffer, std::vector<GameObject> &gameObjects, const Camera &camera);

    private:
        void createPipelineLayout();
        void createPipeline(VkRenderPass renderPass);

        Device &device;

        std::unique_ptr<Pipeline> pipeline;

        VkPipelineLayout pipelineLayout;
    };
}