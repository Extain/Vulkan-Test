#pragma once

#include "camera.h"

#include <vulkan/vulkan.h>

namespace Engine
{
    struct FrameInfo {
        int frameIndex;
        float frameTime;
        VkCommandBuffer commandBuffer;
        Camera &camera;
    };
}