#pragma once

#include "vulkan/vulkan.h"

#include "src/utils/FierceStrings.h"
#include <vector>

#include "VK_CompatibilityChecks.h"
#include "VK_CheckSupport.h"

namespace Fierce {

	class I_DebugTools;

	class VK_Instance :public VK_CheckSupport{
	public:
		VK_Instance();
		~VK_Instance();

		void create();
		VkInstance getId() { return m_instance; }
		I_DebugTools* getDebug() { return m_debug; }

	public:
		bool isDebugSupported() { return m_isDebugSupported; }
		void printSupportedExtensions();
		void printSupportedValidationLayers();
		void printActiveExtensions();
		void printActiveValidationLayers();

	private:
		//Create info
		VkApplicationInfo m_appInfo = {};
		VkInstanceCreateInfo m_createInfo = {};

		//Vulkan objects
		VkInstance m_instance=VK_NULL_HANDLE;

		//Extensions/Validation layers
		ExtensionValidationLayerData m_extensionLayerData = {};

		//Debug
		bool m_isDebugSupported = false;
		I_DebugTools* m_debug = nullptr;

		//Constants
		uint32_t API_VERSION = VK_MAKE_API_VERSION(0, 1, 0, 1);
		std::string APP_NAME = "Fierce-App";
		uint32_t APP_VERSION = VK_MAKE_API_VERSION(0, 1, 0, 1);
		std::string ENGINE_NAME = "Fierce-Engine";
		uint32_t ENGINE_VERSION = VK_MAKE_API_VERSION(0, 1, 0, 1);
	};

}//end namespace