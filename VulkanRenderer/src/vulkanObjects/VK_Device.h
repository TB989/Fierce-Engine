#pragma once

#include "vulkan/vulkan.h"

#include "VK_CompatibilityChecks.h"
#include "VK_CheckSupport.h"

namespace Fierce {

	class VK_CommandPool;
	class VK_CommandBuffer;

	class VK_Device :public VK_CheckSupport{
	public:
		enum QUEUE_TYPE{
			GRAPHICS,TRANSFER
		};

	public:
		VK_Device(VkInstance instance, VkSurfaceKHR surface);
		~VK_Device();

		void create();
		VkDevice getDevice() { return m_device; }
		VkQueue getGraphicsQueue() { return m_graphicsQueue; }
		VkQueue getTransferQueue() { return m_transferQueue; }

	public:
		SurfaceData* getSurfaceData() { return &m_supportedSurfaceData[m_indexActivePhysicalDevice]; }
		DeviceData* getDeviceData() { return &m_supportedDeviceData[m_indexActivePhysicalDevice]; }

		void requerySurfaceData();
		uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
		void submitCommandBuffer(QUEUE_TYPE queue,VkCommandBuffer commandBuffer, VkSemaphore waitSemaphore, VkSemaphore signalSemaphore, VkPipelineStageFlags waitStageMask, VkFence waitFence);
		bool supportsSamplerAnisotropy();
		VK_CommandBuffer* getCommandBuffer(QUEUE_TYPE queue);
		void releaseCommandBuffer(VK_CommandBuffer* commandBuffer);

	public:
		void printActiveData(bool printExtensions, bool printLayers,
			bool printDeviceProperties, bool printDeviceLimits, bool printDeviceFeatures, bool printDeviceMemoryProperties, bool printDeviceQueueFamilies,
			bool printSurfaceData);

		void printSupportedData(bool printExtensions, bool printLayers,
			bool printDeviceProperties, bool printDeviceLimits, bool printDeviceFeatures, bool printDeviceMemoryProperties, bool printDeviceQueueFamilies,
			bool printSurfaceData);

		void printSupportedData(
			int index,
			bool printExtensions, bool printLayers,
			bool printDeviceProperties, bool printDeviceLimits,bool printDeviceFeatures,bool printDeviceMemoryProperties,bool printDeviceQueueFamilies, 
			bool printSurfaceData);

	private:
		void collectPhysicalDeviceData();
		void pickPhysicalDevice();
		void setupQueues();
		void setupExtensionsAndValidationLayers();
		void createLogicalDevice();
		void createCommandPools();

	private:
		void printSupportedExtensions(int index);
		void printSupportedValidationLayers(int index);
		void printActiveExtensions(int index);
		void printActiveValidationLayers(int index);

	private:
		//Create info
		VkDeviceCreateInfo m_deviceCreateInfo = {};
		float m_queuePriority = 1.0f;
		std::vector<VkDeviceQueueCreateInfo> m_queueCreateInfos;

		//Submit info
		VkSubmitInfo m_submitInfo={};

		//Physical device data
		int m_numSupportedPhysicalDevices = 0;
		std::vector<VkPhysicalDevice> m_supportedPhysicalDevices;
		std::vector<DeviceData> m_supportedDeviceData;
		std::vector<SurfaceData> m_supportedSurfaceData;
		std::vector<ExtensionValidationLayerData> m_supportedExtensionValidationLayerData;

		//Vulkan objects
		VkInstance m_instance = VK_NULL_HANDLE;
		VkSurfaceKHR m_surface = VK_NULL_HANDLE;

		int m_indexActivePhysicalDevice = 0;
		VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
		VkDevice m_device = VK_NULL_HANDLE;

		VkQueue m_graphicsQueue = VK_NULL_HANDLE;
		VkQueue m_transferQueue = VK_NULL_HANDLE;

		VK_CommandPool* m_graphicsCommandPool=nullptr;
		VK_CommandPool* m_transferCommandPool = nullptr;
	};

}//end namespace