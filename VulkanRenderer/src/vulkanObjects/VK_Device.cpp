#include "VK_Device.h"

#include "VK_CommandBuffer.h"
#include "VK_Semaphore.h"
#include "VK_Fence.h"
#include "VK_Swapchain.h"

VK_Device::VK_Device(VkInstance instance, VkSurfaceKHR surface){
    m_instance = instance;
    m_surface = surface;
}

VK_Device::~VK_Device() {
    vkDestroyDevice(device, nullptr);
}

void VK_Device::pickPhysicalDevice() {
    std::vector<VkPhysicalDevice> supportedDevices;
    VK_Helper_Device::getAllPhysicalDevices(m_instance,&supportedDevices);

    for (VkPhysicalDevice device:supportedDevices) {
        deviceData = {};
        surfaceData = {};
        extensionLayerData = {};

        VK_Helper_Extensions_ValidationLayers::getExtensions(device, &extensionLayerData.supportedExtensions);
        VK_Helper_Extensions_ValidationLayers::getValidationLayers(device, &extensionLayerData.supportedValidationLayers);
        VK_Helper_Device::getSurfaceData(device, m_surface, &surfaceData);
        VK_Helper_Device::getDeviceData(device,m_surface,&deviceData);

        if (checkDeviceCompatibility(&extensionLayerData, &deviceData, &surfaceData)) {
            m_physicalDevice = device;
            return;
        }
    }

    CHECK_VK(VK_ERROR_INCOMPATIBLE_DRIVER,"No compatible device found.");
}

bool VK_Device::checkDeviceCompatibility(ExtensionValidationLayerData* data, DeviceData* deviceData, SurfaceData* surfaceData) {
    for (auto mcheck : checks) {
        if (!mcheck->check(data, deviceData, surfaceData)) {
            return false;
        }
    }

    return true;
}

void VK_Device::create() {
    pickPhysicalDevice();
    createLogicalDevice();
    vkGetDeviceQueue(device, deviceData.graphicsQueueIndex, 0, &graphicsQueue);
    transferQueue = graphicsQueue;
}

void VK_Device::submitCommandBuffer(VK_CommandBuffer* commandBuffer, VK_Semaphore* waitSemaphore, VK_Semaphore* signalSemaphore, VkPipelineStageFlags waitStageMask, VK_Fence* waitFence){
    VkCommandBuffer cmdBuffer = commandBuffer->getCommandBuffer();

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.pNext = nullptr;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &cmdBuffer;
    if (waitSemaphore!=nullptr) {
        VkSemaphore waitSema = waitSemaphore->getSemaphore();
        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitSemaphores = &waitSema;
    }
    else {
        submitInfo.waitSemaphoreCount = 0;
        submitInfo.pWaitSemaphores = nullptr;
    }
    if (signalSemaphore != nullptr) {
        VkSemaphore signalSema = signalSemaphore->getSemaphore();
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = &signalSema;
    }
    else {
        submitInfo.signalSemaphoreCount = 0;
        submitInfo.pSignalSemaphores = nullptr;
    }
    submitInfo.pWaitDstStageMask = &waitStageMask;

    if (waitFence==nullptr) {
        CHECK_VK(vkQueueSubmit(graphicsQueue, 1, &submitInfo, nullptr), "Failed to submit queue.");
    }
    else {
        CHECK_VK(vkQueueSubmit(graphicsQueue, 1, &submitInfo, waitFence->getFence()), "Failed to submit queue.");
    }
}

uint32_t VK_Device::findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties){
    for (uint32_t i = 0; i < deviceData.deviceMemoryProperties.memoryTypeCount; i++) {
        if ((typeFilter & (1 << i)) && (deviceData.deviceMemoryProperties.memoryTypes[i].propertyFlags & properties) == properties) {
            return i;
        }
    }

    CHECK_VK(VK_ERROR_OUT_OF_DEVICE_MEMORY,"Failed to find memory type.");
    return 0;
}

void VK_Device::createLogicalDevice(){

    VK_Helper_Extensions_ValidationLayers::printValidationLayers(false, "", &extensionLayerData.enabledValidationLayers);
    VK_Helper_Extensions_ValidationLayers::printExtensions(false,"", &extensionLayerData.enabledExtensions);

    VkDeviceQueueCreateInfo queueCreateInfo{};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = deviceData.graphicsQueueIndex;
    queueCreateInfo.queueCount = 1;
    float queuePriority = 1.0f;
    queueCreateInfo.pQueuePriorities = &queuePriority;

    VkPhysicalDeviceFeatures deviceFeatures{};
    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.pNext = nullptr;
    createInfo.flags = 0;
    createInfo.queueCreateInfoCount = 1;
    createInfo.pQueueCreateInfos = &queueCreateInfo;
    createInfo.pEnabledFeatures = &deviceFeatures;
    if (extensionLayerData.enabledExtensions.empty()) {
        createInfo.enabledExtensionCount = 0;
        createInfo.ppEnabledExtensionNames = nullptr;
    }
    else {
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensionLayerData.enabledExtensions.size());
        createInfo.ppEnabledExtensionNames = extensionLayerData.enabledExtensions.data();
    }
    if (extensionLayerData.enabledValidationLayers.empty()) {
        createInfo.enabledLayerCount = 0;
        createInfo.ppEnabledLayerNames = nullptr;
    }
    else {
        createInfo.enabledLayerCount = static_cast<uint32_t>(extensionLayerData.enabledValidationLayers.size());
        createInfo.ppEnabledLayerNames = extensionLayerData.enabledValidationLayers.data();
    }

    CHECK_VK(vkCreateDevice(m_physicalDevice, &createInfo, nullptr, &device), "Failed to create logical device.");
}