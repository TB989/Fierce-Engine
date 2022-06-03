#pragma once

#include "Common.h"

#include "VK_CompatibilityChecks.h"
#include "VK_Helper_Extensions_ValidationLayers.h"
#include "VK_Helper_Device.h"

class VK_CommandBuffer;
class VK_Semaphore;
class VK_Swapchain;

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
	DeviceData* getDeviceData() { return &deviceData; }

	uint32_t getNextImageIndex(VK_Swapchain* swapchain, VK_Semaphore* signalSemaphore);
	void submitCommandBuffer(VK_CommandBuffer* commandBuffer,VK_Semaphore* waitSemaphore,VK_Semaphore* signalSemaphore, VkPipelineStageFlags waitStageMask);
	void presentImage(VK_Swapchain* swapchain, uint32_t imageIndex,VK_Semaphore* waitSemaphore);

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
};