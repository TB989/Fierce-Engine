#pragma once

#include "vulkan/vulkan.h"
#include <vector>

namespace Fierce {

	struct ExtensionValidationLayerData {
		std::vector<VkExtensionProperties> supportedExtensions;
		std::vector<const char*> enabledExtensions;

		std::vector<VkLayerProperties> supportedValidationLayers;
		std::vector<const char*> enabledValidationLayers;
	};

	struct DeviceData {
		VkPhysicalDeviceProperties deviceProperties = {};
		VkPhysicalDeviceFeatures supportedDeviceFeatures = {};
		VkPhysicalDeviceFeatures enabledDeviceFeatures = {};
		VkPhysicalDeviceMemoryProperties deviceMemoryProperties = {};
		std::vector<VkQueueFamilyProperties> queueFamilies;
		std::vector<bool> presentSupport;

		int graphicsQueueIndex = -1;
		int transferQueueIndex = -1;
		int computeQueueIndex = -1;

		bool hasDedicatedTransferQueue = false;
	};

	struct SurfaceData {
		VkSurfaceCapabilitiesKHR surfaceCapabilities = {};
		std::vector<VkSurfaceFormatKHR> surfaceFormats;
		std::vector<VkPresentModeKHR> presentModes;

		VkSurfaceFormatKHR swapchainFormat = {};
		VkPresentModeKHR swapchainPresentMode = {};
		uint32_t swapchainWidth = 0;
		uint32_t swapchainHeight = 0;
	};

	class VK_CompatibilityCheck_Device {
	public:
		virtual bool check(ExtensionValidationLayerData* data1, DeviceData* data2, SurfaceData* data3) = 0;
	};

	class VK_Check_Device_Extensions :public VK_CompatibilityCheck_Device {
	public:
		VK_Check_Device_Extensions(bool required, std::vector<const char*> extensions) {
			m_required = required;
			m_extensions = extensions;
		}

		bool check(ExtensionValidationLayerData* data1, DeviceData* data2, SurfaceData* data3);

	private:
		bool m_required;
		std::vector<const char*> m_extensions;

		bool isExtensionSupported(const char* extensionName, std::vector<VkExtensionProperties>* supportedExtensions);
	};

	class VK_Check_Device_ValidationLayers :public VK_CompatibilityCheck_Device {
	public:
		VK_Check_Device_ValidationLayers(bool required, std::vector<const char*> layers) {
			m_required = required;
			m_layers = layers;
		}

		bool check(ExtensionValidationLayerData* data1, DeviceData* data2, SurfaceData* data3);

	private:
		bool m_required;
		std::vector<const char*> m_layers;

		bool isValidationLayerSupported(const char* layerName, std::vector<VkLayerProperties>* supportedLayers);
	};

	class VK_Check_Device_General :public VK_CompatibilityCheck_Device {
	public:
		VK_Check_Device_General() {};

		bool check(ExtensionValidationLayerData* data1, DeviceData* data2, SurfaceData* data3);
	};

	class VK_Check_Device_Queues :public VK_CompatibilityCheck_Device {
	public:
		VK_Check_Device_Queues() {};

		bool check(ExtensionValidationLayerData* data1, DeviceData* data2, SurfaceData* data3);
	};

	class VK_Check_Device_Surface_Format :public VK_CompatibilityCheck_Device {
	public:
		VK_Check_Device_Surface_Format(std::vector<VkFormat> formats) {
			m_formats = formats;
		};

		bool check(ExtensionValidationLayerData* data1, DeviceData* data2, SurfaceData* data3);

	private:
		std::vector<VkFormat> m_formats;
	};

	class VK_Check_Device_Surface_PresentMode :public VK_CompatibilityCheck_Device {
	public:
		VK_Check_Device_Surface_PresentMode(std::vector<VkPresentModeKHR> presentModes) {
			m_presentModes = presentModes;
		};

		bool check(ExtensionValidationLayerData* data1, DeviceData* data2, SurfaceData* data3);

	private:
		std::vector<VkPresentModeKHR> m_presentModes;
	};

	class VK_Check_Sampler_Anisotropy :public VK_CompatibilityCheck_Device {
	public:
		VK_Check_Sampler_Anisotropy() {

		}

		bool check(ExtensionValidationLayerData* data1, DeviceData* data2, SurfaceData* data3);
	};

}//end namespace