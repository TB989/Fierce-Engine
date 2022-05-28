#pragma once

#include "Common.h"

#include "VK_CompatibilityChecks.h"
#include "VK_Helper_Extensions_ValidationLayers.h"
#include "VK_Helper_Device.h"

class VK_Renderpass;
class VK_Framebuffers;
class VK_Pipeline;
class VK_Buffer;

class VK_Device{
public:
	VK_Device(VkInstance instance, VkSurfaceKHR surface);
	~VK_Device();

public:
	void addCheck(VK_CompatibilityCheck_Device* check) { checks.push_back(check); }

	void create();
	VkDevice getDevice() { return device; }
	VkQueue getQueue() { return graphicsQueue; }

	SurfaceData* getSurfaceData() { return &surfaceData; }

	void createCommandPool();
	void createCommandBuffers(int numBuffers);
	void recordCommandBuffers(VK_Renderpass* renderpass, VK_Framebuffers* framebuffers, VK_Pipeline* pipeline, VK_Buffer* vertexBuffer, VK_Buffer* indexBuffer);
	VkCommandBuffer getCommandBuffer(int index) { return commandBuffers[index]; }

	void copyBuffer(int size, VkBuffer srcBuffer, VkBuffer dstBuffer);

	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

private:
	void pickPhysicalDevice();
	bool checkDeviceCompatibility(ExtensionValidationLayerData* data, DeviceData* deviceData, SurfaceData* surfaceData);

	void createLogicalDevice();

private:
	VkInstance m_instance=VK_NULL_HANDLE;
	VkSurfaceKHR m_surface=VK_NULL_HANDLE;

	std::vector<VK_CompatibilityCheck_Device*> checks;

	VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
	DeviceData deviceData;
	SurfaceData surfaceData;
	ExtensionValidationLayerData extensionLayerData;

	VkDevice device=VK_NULL_HANDLE;
	VkQueue graphicsQueue=VK_NULL_HANDLE;
	VkQueue transferQueue = VK_NULL_HANDLE;

	VkCommandPool commandPool;
	std::vector<VkCommandBuffer> commandBuffers;
};