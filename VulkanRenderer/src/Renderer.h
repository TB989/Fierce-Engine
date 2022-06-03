#pragma once

#include "VK_Semaphore.h"
#include "VK_Fence.h"
#include "VK_Buffer.h"
#include "VK_CommandPool.h"
#include "VK_CommandBuffer.h"
#include "VK_DescriptorSet.h"

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