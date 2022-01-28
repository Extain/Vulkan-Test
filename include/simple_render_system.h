#pragma once

#include "pipeline.h"
#include "device.h"
#include "gameObject.h"
#include "camera.h"
#include "frameInfo.h"

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

        void renderGameObjects(FrameInfo &frameInfo, std::vector<GameObject> &gameObjects);

    private:
        void createPipelineLayout();
        void createPipeline(VkRenderPass renderPass);

        Device &device;

        std::unique_ptr<Pipeline> pipeline;

        VkPipelineLayout pipelineLayout;
    };
}