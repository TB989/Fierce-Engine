#include "VK_Instance.h"

#include "src/VulkanRenderer/renderSystem/RenderSystem.h"

#include "src/VulkanRenderer/vulkanObjects/VK_DebugTools.h"

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

        m_extensionLayerData = {};
        VK_Helper_Extensions_ValidationLayers::getExtensions(nullptr, &m_extensionLayerData.supportedExtensions);
        VK_Helper_Extensions_ValidationLayers::getValidationLayers(nullptr, &m_extensionLayerData.supportedValidationLayers);

        m_isDebugSupported = VK_Helper_Extensions_ValidationLayers::isExtensionSupported(VK_EXT_DEBUG_UTILS_EXTENSION_NAME, &m_extensionLayerData.supportedExtensions);
    }

    VK_Instance::~VK_Instance() {
        delete m_debug;
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

            m_debug = new VK_DebugTools_debug();

            m_createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&m_debug->getDebugInfo();
            if (vkCreateInstance(&m_createInfo, nullptr, &m_instance) != VK_SUCCESS) {
                RenderSystem::LOGGER->error("Failed to create instance.");
            }

            m_debug->create(m_instance);
        }
        else {
            RenderSystem::LOGGER->info("Debug messenger is not active.");

            m_debug = new VK_DebugTools_dummy();

            if (vkCreateInstance(&m_createInfo, nullptr, &m_instance) != VK_SUCCESS) {
                RenderSystem::LOGGER->error("Failed to create instance.");
            }

            m_debug->create(m_instance);
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
}