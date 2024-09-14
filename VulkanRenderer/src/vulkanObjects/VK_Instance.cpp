#include "VK_Instance.h"

#include "renderSystem/RenderSystem.h"

#include "VK_Helper_Extensions_ValidationLayers.h"

namespace Fierce {

    VK_Instance::VK_Instance() {
        m_appInfo={};
        m_appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        m_appInfo.pNext = nullptr;
        m_appInfo.pApplicationName = APP_NAME.c_str();
        m_appInfo.applicationVersion = APP_VERSION;
        m_appInfo.pEngineName = ENGINE_NAME.c_str();
        m_appInfo.engineVersion = ENGINE_VERSION;
        m_appInfo.apiVersion = API_VERSION;

        m_createInfo = {};
        m_createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        m_createInfo.pNext = nullptr;
        m_createInfo.flags = 0;
        m_createInfo.pApplicationInfo = &m_appInfo;
        m_createInfo.enabledExtensionCount = 0;
        m_createInfo.ppEnabledExtensionNames = nullptr;
        m_createInfo.enabledLayerCount = 0;
        m_createInfo.ppEnabledLayerNames = nullptr;

        m_debugCreateInfo={};
        m_debugCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        m_debugCreateInfo.pNext = nullptr;
        m_debugCreateInfo.flags = 0;
        m_debugCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        m_debugCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        m_debugCreateInfo.pfnUserCallback = debugCallback;
        m_debugCreateInfo.pUserData = nullptr;

        m_extensionLayerData = {};
        VK_Helper_Extensions_ValidationLayers::getExtensions(nullptr, &m_extensionLayerData.supportedExtensions);
        VK_Helper_Extensions_ValidationLayers::getValidationLayers(nullptr, &m_extensionLayerData.supportedValidationLayers);

        m_isDebugSupported = VK_Helper_Extensions_ValidationLayers::isExtensionSupported(VK_EXT_DEBUG_UTILS_EXTENSION_NAME, &m_extensionLayerData.supportedExtensions);
    }

    VK_Instance::~VK_Instance() {
        if (m_isDebugSupported) {
            vkDestroyDebugUtilsMessengerEXT(m_instance, m_debugMessenger, nullptr);
        }
        vkDestroyInstance(m_instance, nullptr);
    }

    void VK_Instance::create() {
        if (!doChecks(&m_extensionLayerData, nullptr, nullptr)) {
            RenderSystem::LOGGER->error("Instance is incompatible.");
        }

        if (m_extensionLayerData.enabledExtensions.empty()) {
            m_createInfo.enabledExtensionCount = 0;
            m_createInfo.ppEnabledExtensionNames = nullptr;
        }
        else {
            m_createInfo.enabledExtensionCount = static_cast<uint32_t>(m_extensionLayerData.enabledExtensions.size());
            m_createInfo.ppEnabledExtensionNames = m_extensionLayerData.enabledExtensions.data();
        }
        if (m_extensionLayerData.enabledValidationLayers.empty()) {
            m_createInfo.enabledLayerCount = 0;
            m_createInfo.ppEnabledLayerNames = nullptr;
        }
        else {
            m_createInfo.enabledLayerCount = static_cast<uint32_t>(m_extensionLayerData.enabledValidationLayers.size());
            m_createInfo.ppEnabledLayerNames = m_extensionLayerData.enabledValidationLayers.data();
        }

        if (m_isDebugSupported) {
            RenderSystem::LOGGER->info("Debug messenger is active.");

            m_createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&m_debugCreateInfo;
            if (vkCreateInstance(&m_createInfo, nullptr, &m_instance) != VK_SUCCESS) {
                RenderSystem::LOGGER->error("Failed to create instance.");
            }

            vkCreateDebugUtilsMessengerEXT = loadCreateFunctionPointer(m_instance);
            vkDestroyDebugUtilsMessengerEXT = loadDestroyFunctionPointer(m_instance);

            if (vkCreateDebugUtilsMessengerEXT(m_instance, &m_debugCreateInfo, nullptr, &m_debugMessenger) != VK_SUCCESS) {
                RenderSystem::LOGGER->error("Failed to create debug messenger.");
            }
        }
        else {
            RenderSystem::LOGGER->info("Debug messenger is not active.");

            if (vkCreateInstance(&m_createInfo, nullptr, &m_instance) != VK_SUCCESS) {
                RenderSystem::LOGGER->error("Failed to create instance.");
            }
        }
    }

    void VK_Instance::printSupportedExtensions(){
        VK_Helper_Extensions_ValidationLayers::printExtensions(true, "supported", &m_extensionLayerData.supportedExtensions);
    }

    void VK_Instance::printSupportedValidationLayers(){
        VK_Helper_Extensions_ValidationLayers::printValidationLayers(true, "supported",&m_extensionLayerData.supportedValidationLayers);
    }

    void VK_Instance::printActiveExtensions(){
        if (m_instance == VK_NULL_HANDLE) {
            RenderSystem::LOGGER->warn("Cannot print active instance extensions yet, instance must have been created.");
        }
        else {
            VK_Helper_Extensions_ValidationLayers::printExtensions(true, "active", &m_extensionLayerData.enabledExtensions);
        }
    }

    void VK_Instance::printActiveValidationLayers(){
        if (m_instance == VK_NULL_HANDLE) {
            RenderSystem::LOGGER->warn("Cannot print active instance validation layers yet, instance must have been created.");
        }
        else {
            VK_Helper_Extensions_ValidationLayers::printValidationLayers(true, "active", &m_extensionLayerData.enabledValidationLayers);
        }
    }

    PFN_vkCreateDebugUtilsMessengerEXT VK_Instance::loadCreateFunctionPointer(VkInstance instance) {
        PFN_vkCreateDebugUtilsMessengerEXT func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");

        if (func == nullptr) {
            RenderSystem::LOGGER->error("Failed to load function pointer for vkCreateDebugUtilsMessengerEXT.");
            return nullptr;
        }
        return func;
    }

    PFN_vkDestroyDebugUtilsMessengerEXT VK_Instance::loadDestroyFunctionPointer(VkInstance instance) {
        PFN_vkDestroyDebugUtilsMessengerEXT func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");

        if (func == nullptr) {
            RenderSystem::LOGGER->error("Failed to load function pointer for vkDestroyDebugUtilsMessengerEXT.");
            return nullptr;
        }
        return func;
    }

    VKAPI_ATTR VkBool32 VKAPI_CALL VK_Instance::debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
        RenderSystem::LOGGER->error("%s", pCallbackData->pMessage);
        return VK_FALSE;
    }

}