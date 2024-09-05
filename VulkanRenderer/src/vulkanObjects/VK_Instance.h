#pragma once

#include "vulkan/vulkan.h"
#include "src/FierceStrings.h"
#include "src/Logger.h"

namespace Fierce {

	class VK_Instance {
	public:
		VK_Instance();
		~VK_Instance();

		void create();

	private:
		Logger* m_logger;

		VkApplicationInfo m_appInfo;
		VkInstanceCreateInfo m_createInfo;
		VkInstance m_instance;

		uint32_t API_VERSION = VK_MAKE_API_VERSION(0, 1, 0, 0);
		std::string APP_NAME = "Fierce-App";
		uint32_t APP_VERSION = VK_MAKE_API_VERSION(0, 1, 0, 0);
		std::string ENGINE_NAME = "Fierce-Engine";
		uint32_t ENGINE_VERSION = VK_MAKE_API_VERSION(0, 1, 3, 0);
	};

}//end namespace