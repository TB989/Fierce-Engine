#pragma once

#include "vulkan/vulkan.h"

#include "src/FierceStrings.h"
#include <vector>

#include "VK_CompatibilityChecks.h"
#include "VK_CheckSupport.h"

namespace Fierce {

	class VK_Instance :public VK_CheckSupport{
	public:
		VK_Instance();
		~VK_Instance();

		void create();
		VkInstance getId() { return m_instance; }

	public:
		bool isDebugSupported() { return m_isDebugSupported; }
		void printSupportedExtensions();
		void printSupportedValidationLayers();
		void printActiveExtensions();
		void printActiveValidationLayers();

	private:
		PFN_vkCreateDebugUtilsMessengerEXT loadCreateFunctionPointer(VkInstance instance);
		PFN_vkDestroyDebugUtilsMessengerEXT loadDestroyFunctionPointer(VkInstance instance);
		static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);

	private:
		//Create info
		VkApplicationInfo m_appInfo = {};
		VkInstanceCreateInfo m_createInfo = {};
		VkDebugUtilsMessengerCreateInfoEXT m_debugCreateInfo = {};

		//Vulkan objects
		VkInstance m_instance=VK_NULL_HANDLE;
		VkDebugUtilsMessengerEXT m_debugMessenger = VK_NULL_HANDLE;

		//Extensions/Validation layers
		ExtensionValidationLayerData m_extensionLayerData = {};

		//Debug misc
		bool m_isDebugSupported = false;
		PFN_vkCreateDebugUtilsMessengerEXT vkCreateDebugUtilsMessengerEXT = VK_NULL_HANDLE;
		PFN_vkDestroyDebugUtilsMessengerEXT vkDestroyDebugUtilsMessengerEXT = VK_NULL_HANDLE;

		//Constants
		uint32_t API_VERSION = VK_MAKE_API_VERSION(0, 1, 0, 1);
		std::string APP_NAME = "Fierce-App";
		uint32_t APP_VERSION = VK_MAKE_API_VERSION(0, 1, 0, 1);
		std::string ENGINE_NAME = "Fierce-Engine";
		uint32_t ENGINE_VERSION = VK_MAKE_API_VERSION(0, 1, 0, 1);
	};

}//end namespace