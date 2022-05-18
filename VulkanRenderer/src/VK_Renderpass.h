#pragma once

#include "Common.h"

class VK_Device;

class VK_Renderpass {
public:
	VK_Renderpass(VK_Device* device);
	~VK_Renderpass();

	VkRenderPass getRenderpass() { return renderPass; }

private:
	VkDevice m_device;
	VkRenderPass renderPass;
};