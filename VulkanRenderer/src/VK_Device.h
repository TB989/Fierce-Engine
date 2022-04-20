#pragma once

#include "src/utils/FierceStrings.h"
#include "VK_Helper_Extensions_ValidationLayers.h"
#include "VK_CompatibilityChecks.h"

#include "vulkan/vulkan.h"
#include <vector>

class VK_CommandBuffer;

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

	VK_CommandBuffer* getCommandBuffer();

private:
	void pickPhysicalDevice();
	bool checkDeviceCompatibility(ExtensionValidationLayerData* data, DeviceData* deviceData, SurfaceData* surfaceData);

	void createLogicalDevice();

	void createCommandPool();

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
};