#pragma once

#include "vulkanObjects/VK_Semaphore.h"
#include "vulkanObjects/VK_Fence.h"
#include "vulkanObjects/VK_Buffer.h"
#include "vulkanObjects/VK_CommandPool.h"
#include "vulkanObjects/VK_CommandBuffer.h"
#include "vulkanObjects/VK_DescriptorSet.h"

struct FrameData {
	VK_Semaphore* imageAvailableSemaphore;
	VK_Semaphore* renderFinishedSemaphore;
	VK_Fence* renderFinishedFence;

	VK_CommandPool* commandPool;
	VK_CommandBuffer* commandBuffer;

	VK_Buffer* UBO;
	VK_DescriptorSet* descriptorSet;
};

void beginFrame();
void endFrame();