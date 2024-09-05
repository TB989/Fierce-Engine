#include "VK_Instance.h"

namespace Fierce {

	VK_Instance::VK_Instance(){
        m_logger = new Logger("VK",true,"ALL_LOGS");

        m_appInfo={};
        m_appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        m_appInfo.pNext = nullptr;
        m_appInfo.pApplicationName = APP_NAME.c_str();
        m_appInfo.applicationVersion = APP_VERSION;
        m_appInfo.pEngineName = ENGINE_NAME.c_str();
        m_appInfo.engineVersion = ENGINE_VERSION;
        m_appInfo.apiVersion = API_VERSION;
	}

    VK_Instance::~VK_Instance(){
        vkDestroyInstance(m_instance,nullptr);
    }

    void VK_Instance::create(){
        m_createInfo={};
        m_createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        m_createInfo.pNext = nullptr;
        m_createInfo.flags = 0;
        m_createInfo.pApplicationInfo = &m_appInfo;
        m_createInfo.enabledLayerCount = 0;
        m_createInfo.ppEnabledLayerNames = nullptr;
        m_createInfo.enabledExtensionCount = 0;
        m_createInfo.ppEnabledExtensionNames = nullptr;

        if (vkCreateInstance(&m_createInfo, nullptr, &m_instance) != VK_SUCCESS) {
            m_logger->error("Failed to create vulkan instance.");
        }

        m_logger->info("Created vulkan instance.");
    }

}//end namespace