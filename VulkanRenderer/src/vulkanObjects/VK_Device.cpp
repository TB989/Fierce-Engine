#include "VK_Device.h"

#include "renderSystem/RenderSystem.h"

#include "VK_Helper_Extensions_ValidationLayers.h"
#include "VK_HelperDevice.h"

namespace Fierce {

    VK_Device::VK_Device(VkInstance instance, VkSurfaceKHR surface) {
        m_instance = instance;
        m_surface = surface;

        m_queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        m_queueCreateInfo.pNext = nullptr;
        m_queueCreateInfo.flags = 0;
        m_queueCreateInfo.queueFamilyIndex = 0;
        m_queueCreateInfo.queueCount = 1;
        m_queueCreateInfo.pQueuePriorities = &m_queuePriority;

        m_deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        m_deviceCreateInfo.pNext = nullptr;
        m_deviceCreateInfo.flags = 0;
        m_deviceCreateInfo.queueCreateInfoCount = 1;
        m_deviceCreateInfo.pQueueCreateInfos = &m_queueCreateInfo;
        m_deviceCreateInfo.enabledExtensionCount = 0;
        m_deviceCreateInfo.ppEnabledExtensionNames = nullptr;
        m_deviceCreateInfo.enabledLayerCount = 0;
        m_deviceCreateInfo.ppEnabledLayerNames = nullptr;
        m_deviceCreateInfo.pEnabledFeatures = nullptr;

        m_submitInfo={};
        m_submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        m_submitInfo.pNext = nullptr;

        VK_Helper_Device::getAllPhysicalDevices(m_instance, &m_supportedPhysicalDevices);
        m_numSupportedPhysicalDevices = m_supportedPhysicalDevices.size();
        collectPhysicalDeviceData();
    }

    VK_Device::~VK_Device() {
        vkDestroyDevice(m_device, nullptr);
    }

    void VK_Device::collectPhysicalDeviceData(){
        for (int i = 0;i<m_numSupportedPhysicalDevices;i++) {
            DeviceData m_deviceData = {};
            SurfaceData m_surfaceData= {};
            ExtensionValidationLayerData m_extensionLayerData = {};

            VK_Helper_Extensions_ValidationLayers::getExtensions(m_supportedPhysicalDevices[i], &m_extensionLayerData.supportedExtensions);
            VK_Helper_Extensions_ValidationLayers::getValidationLayers(m_supportedPhysicalDevices[i], &m_extensionLayerData.supportedValidationLayers);
            VK_Helper_Device::getSurfaceData(m_supportedPhysicalDevices[i], m_surface, &m_surfaceData);
            VK_Helper_Device::getDeviceData(m_supportedPhysicalDevices[i], m_surface, &m_deviceData);

            m_supportedDeviceData.push_back(m_deviceData);
            m_supportedSurfaceData.push_back(m_surfaceData);
            m_supportedExtensionValidationLayerData.push_back(m_extensionLayerData);
        }
    }

    void VK_Device::pickPhysicalDevice() {
        for (int i = 0; i < m_numSupportedPhysicalDevices; i++) {
            if (doChecks(&m_supportedExtensionValidationLayerData[i], &m_supportedDeviceData[i], &m_supportedSurfaceData[i])) {
                m_physicalDevice = m_supportedPhysicalDevices[i];
                m_indexActivePhysicalDevice = i;
                return;
            }
        }

        RenderSystem::LOGGER->error("No compatible device found.");
    }

    void VK_Device::create() {
        pickPhysicalDevice();
        createLogicalDevice();
        vkGetDeviceQueue(m_device, m_supportedDeviceData[m_indexActivePhysicalDevice].graphicsQueueIndex, 0, &m_graphicsQueue);
        m_transferQueue = m_graphicsQueue;
    }

    void VK_Device::requerySurfaceData(){
        VK_Helper_Device::getSurfaceData(m_supportedPhysicalDevices[m_indexActivePhysicalDevice], m_surface, &m_supportedSurfaceData[m_indexActivePhysicalDevice]);
    }

    void VK_Device::submitCommandBuffer(VkCommandBuffer commandBuffer, VkSemaphore waitSemaphore, VkSemaphore signalSemaphore, VkPipelineStageFlags waitStageMask, VkFence waitFence) {
        m_submitInfo.commandBufferCount = 1;
        m_submitInfo.pCommandBuffers = &commandBuffer;

        if (waitSemaphore != VK_NULL_HANDLE) {
            m_submitInfo.waitSemaphoreCount = 1;
            m_submitInfo.pWaitSemaphores = &waitSemaphore;
        }
        else {
            m_submitInfo.waitSemaphoreCount = 0;
            m_submitInfo.pWaitSemaphores = nullptr;
        }

        if (signalSemaphore != VK_NULL_HANDLE) {
            m_submitInfo.signalSemaphoreCount = 1;
            m_submitInfo.pSignalSemaphores = &signalSemaphore;
        }
        else {
            m_submitInfo.signalSemaphoreCount = 0;
            m_submitInfo.pSignalSemaphores = nullptr;
        }

        m_submitInfo.pWaitDstStageMask = &waitStageMask;

        if (waitFence == VK_NULL_HANDLE) {
            if (vkQueueSubmit(m_graphicsQueue, 1, &m_submitInfo, nullptr)!=VK_SUCCESS) {
                RenderSystem::LOGGER->error("Failed to submit queue.");
            }
        }
        else {
            if (vkQueueSubmit(m_graphicsQueue, 1, &m_submitInfo, waitFence)) {
                RenderSystem::LOGGER->error("Failed to submit queue.");
            }
        }
    }

    void VK_Device::printActiveData(bool printExtensions, bool printLayers, bool printDeviceProperties, bool printDeviceLimits, bool printDeviceFeatures, bool printDeviceMemoryProperties, bool printDeviceQueueFamilies, bool printSurfaceData){
        if (printExtensions) {
            printActiveExtensions(m_indexActivePhysicalDevice);
        }
        if (printLayers) {
            printActiveValidationLayers(m_indexActivePhysicalDevice);
        }
        if (printDeviceProperties) {
            VK_Helper_Device::printDeviceProperties(&m_supportedDeviceData[m_indexActivePhysicalDevice]);
        }
        if (printDeviceLimits) {
            VK_Helper_Device::printDeviceLimits(&m_supportedDeviceData[m_indexActivePhysicalDevice]);
        }
        if (printDeviceFeatures) {
            VK_Helper_Device::printActiveDeviceFeatures(&m_supportedDeviceData[m_indexActivePhysicalDevice]);
        }
        if (printDeviceMemoryProperties) {
            VK_Helper_Device::printDeviceMemoryProperties(&m_supportedDeviceData[m_indexActivePhysicalDevice]);
        }
        if (printDeviceQueueFamilies) {
            DeviceData* data = &m_supportedDeviceData[m_indexActivePhysicalDevice];

            RenderSystem::LOGGER->info("Queue family graphics:");
            VkQueueFamilyProperties family = data->queueFamilies[data->graphicsQueueIndex];
            std::string flags = "";
            RenderSystem::LOGGER->info("\tQueueCount: %i", family.queueCount);
            if (family.queueFlags & VK_QUEUE_COMPUTE_BIT) {
                flags.append(" COMPUTE_BIT");
            }
            if (family.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                flags.append(" GRAPHICS_BIT");
            }
            if (family.queueFlags & VK_QUEUE_TRANSFER_BIT) {
                flags.append(" TRANSFER_BIT");
            }
            if (family.queueFlags & VK_QUEUE_SPARSE_BINDING_BIT) {
                flags.append(" SPARSE_BINDING_BIT");
            }
            RenderSystem::LOGGER->info("\tQueueFlags: %s", flags.c_str());
            RenderSystem::LOGGER->info("");

            RenderSystem::LOGGER->info("Queue family transfer:");
            family = data->queueFamilies[data->transferQueueIndex];
            flags = "";
            RenderSystem::LOGGER->info("\tQueueCount: %i", family.queueCount);
            if (family.queueFlags & VK_QUEUE_COMPUTE_BIT) {
                flags.append(" COMPUTE_BIT");
            }
            if (family.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                flags.append(" GRAPHICS_BIT");
            }
            if (family.queueFlags & VK_QUEUE_TRANSFER_BIT) {
                flags.append(" TRANSFER_BIT");
            }
            if (family.queueFlags & VK_QUEUE_SPARSE_BINDING_BIT) {
                flags.append(" SPARSE_BINDING_BIT");
            }
            RenderSystem::LOGGER->info("\tQueueFlags: %s", flags.c_str());
            RenderSystem::LOGGER->info("");
        }
        if (printSurfaceData) {
            SurfaceData* surfaceData = &m_supportedSurfaceData[m_indexActivePhysicalDevice];

            RenderSystem::LOGGER->info("##### Surface Data #####");
            RenderSystem::LOGGER->info("\tSwapchain format:");
            switch (surfaceData->swapchainFormat.format) {
            case VK_FORMAT_B8G8R8A8_UNORM:
                RenderSystem::LOGGER->info("\tVK_FORMAT_B8G8R8A8_UNORM VK_COLOR_SPACE_SRGB_NONLINEAR_KHR");
                break;
            case VK_FORMAT_B8G8R8A8_SRGB:
                RenderSystem::LOGGER->info("\tVK_FORMAT_B8G8R8A8_SRGB VK_COLOR_SPACE_SRGB_NONLINEAR_KHR");
                break;
            case VK_FORMAT_A2B10G10R10_UNORM_PACK32:
                RenderSystem::LOGGER->info("\tVK_FORMAT_A2B10G10R10_UNORM_PACK32 VK_COLOR_SPACE_SRGB_NONLINEAR_KHR");
                break;
            default:
                RenderSystem::LOGGER->info("\t%i %i", surfaceData->swapchainFormat.format, surfaceData->swapchainFormat.colorSpace);
                break;
            }
            RenderSystem::LOGGER->info("\tSwapchain present mode:");
            switch (surfaceData->swapchainPresentMode) {
            case VK_PRESENT_MODE_IMMEDIATE_KHR:
                RenderSystem::LOGGER->info("\tVK_PRESENT_MODE_IMMEDIATE_KHR");
                break;
            case VK_PRESENT_MODE_MAILBOX_KHR:
                RenderSystem::LOGGER->info("\tVK_PRESENT_MODE_MAILBOX_KHR");
                break;
            case VK_PRESENT_MODE_FIFO_KHR:
                RenderSystem::LOGGER->info("\tVK_PRESENT_MODE_FIFO_KHR");
                break;
            case VK_PRESENT_MODE_FIFO_RELAXED_KHR:
                RenderSystem::LOGGER->info("\tVK_PRESENT_MODE_FIFO_RELAXED_KHR");
                break;
            }
            RenderSystem::LOGGER->info("#######################");
        }
    }

    void VK_Device::printSupportedData(bool printExtensions, bool printLayers, bool printDeviceProperties, bool printDeviceLimits, bool printDeviceFeatures, bool printDeviceMemoryProperties, bool printDeviceQueueFamilies, bool printSurfaceData) {
        for (int i = 0;i<m_numSupportedPhysicalDevices;i++) {
            std::string deviceType;
            switch (m_supportedDeviceData[i].deviceProperties.deviceType) {
            case VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_OTHER:
                deviceType = "Other";
                break;
            case VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
                deviceType = "Integrated GPU";
                break;
            case VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
                deviceType = "Discrete GPU";
                break;
            case VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
                deviceType = "Virtual GPU";
                break;
            case VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_CPU:
                deviceType = "CPU";
                break;
            }
            RenderSystem::LOGGER->info("######################################################################################################");
            RenderSystem::LOGGER->info("######################## Device: %s (%s) ################################", m_supportedDeviceData[i].deviceProperties.deviceName, deviceType.c_str());
            RenderSystem::LOGGER->info("######################################################################################################");
            printSupportedData(i, printExtensions, printLayers, printDeviceProperties, printDeviceLimits, printDeviceFeatures, printDeviceMemoryProperties, printDeviceQueueFamilies, printSurfaceData);
        }
    }

    void VK_Device::printSupportedData(int index,bool printExtensions, bool printLayers,bool printDeviceProperties, bool printDeviceLimits, bool printDeviceFeatures, bool printDeviceMemoryProperties, bool printDeviceQueueFamilies,bool printSurfaceData){
        if (printExtensions) {
            printSupportedExtensions(index);
        }
        if (printLayers) {
            printSupportedValidationLayers(index);
        }
        if (printDeviceProperties||printDeviceLimits||printDeviceFeatures||printDeviceMemoryProperties||printDeviceQueueFamilies) {
            VK_Helper_Device::printDeviceData(&m_supportedDeviceData[index], printDeviceProperties,printDeviceLimits,printDeviceFeatures,printDeviceMemoryProperties,printDeviceQueueFamilies);
        }
        if (printSurfaceData) {
            VK_Helper_Device::printSurfaceData(&m_supportedSurfaceData[index]);
        }
    }

    void VK_Device::printSupportedExtensions(int index) {
        VK_Helper_Extensions_ValidationLayers::printExtensions(false, "supported", &m_supportedExtensionValidationLayerData[index].supportedExtensions);
    }

    void VK_Device::printSupportedValidationLayers(int index) {
        VK_Helper_Extensions_ValidationLayers::printValidationLayers(false, "supported", &m_supportedExtensionValidationLayerData[index].supportedValidationLayers);
    }

    void VK_Device::printActiveExtensions(int index) {
        if (m_device == VK_NULL_HANDLE) {
            RenderSystem::LOGGER->warn("Cannot print active device extensions yet, device must have been created.");
        }
        else {
            VK_Helper_Extensions_ValidationLayers::printExtensions(false, "active", &m_supportedExtensionValidationLayerData[index].enabledExtensions);
        }
    }

    void VK_Device::printActiveValidationLayers(int index) {
        if (m_device == VK_NULL_HANDLE) {
            RenderSystem::LOGGER->warn("Cannot print active device validation layers yet, device must have been created.");
        }
        else {
            VK_Helper_Extensions_ValidationLayers::printValidationLayers(false, "active", &m_supportedExtensionValidationLayerData[index].enabledValidationLayers);
        }
    }

    void VK_Device::createLogicalDevice() {
        m_queueCreateInfo.queueFamilyIndex = m_supportedDeviceData[m_indexActivePhysicalDevice].graphicsQueueIndex;

        m_deviceCreateInfo.pEnabledFeatures = &m_supportedDeviceData[m_indexActivePhysicalDevice].enabledDeviceFeatures;

        if (m_supportedExtensionValidationLayerData[m_indexActivePhysicalDevice].enabledExtensions.empty()) {
            m_deviceCreateInfo.enabledExtensionCount = 0;
            m_deviceCreateInfo.ppEnabledExtensionNames = nullptr;
        }
        else {
            m_deviceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(m_supportedExtensionValidationLayerData[m_indexActivePhysicalDevice].enabledExtensions.size());
            m_deviceCreateInfo.ppEnabledExtensionNames = m_supportedExtensionValidationLayerData[m_indexActivePhysicalDevice].enabledExtensions.data();
        }
        if (m_supportedExtensionValidationLayerData[m_indexActivePhysicalDevice].enabledValidationLayers.empty()) {
            m_deviceCreateInfo.enabledLayerCount = 0;
            m_deviceCreateInfo.ppEnabledLayerNames = nullptr;
        }
        else {
            m_deviceCreateInfo.enabledLayerCount = static_cast<uint32_t>(m_supportedExtensionValidationLayerData[m_indexActivePhysicalDevice].enabledValidationLayers.size());
            m_deviceCreateInfo.ppEnabledLayerNames = m_supportedExtensionValidationLayerData[m_indexActivePhysicalDevice].enabledValidationLayers.data();
        }

        if (vkCreateDevice(m_physicalDevice, &m_deviceCreateInfo, nullptr, &m_device)!=VK_SUCCESS) {
            RenderSystem::LOGGER->error("Failed to create logical device.");
        }
    }

}//end namespace