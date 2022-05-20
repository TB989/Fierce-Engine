#include "VK_Device.h"

#include "VK_Renderpass.h"
#include "VK_Framebuffers.h"
#include "VK_Pipeline.h"
#include "VK_Buffer.h"

VK_Device::VK_Device(VkInstance instance, VkSurfaceKHR surface){
    m_instance = instance;
    m_surface = surface;
}

VK_Device::~VK_Device() {
    vkFreeCommandBuffers(device, commandPool, commandBuffers.size(), commandBuffers.data());
    vkDestroyCommandPool(device, commandPool, nullptr);
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

void VK_Device::createCommandPool(){
    VkCommandPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.pNext = nullptr;
    poolInfo.flags = 0;
    poolInfo.queueFamilyIndex = deviceData.graphicsQueueIndex;

    CHECK_VK(vkCreateCommandPool(device, &poolInfo, nullptr, &commandPool), "Failed to create command pool.");
}

void VK_Device::createCommandBuffers(int numBuffers){
    commandBuffers.resize(numBuffers);

    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.pNext = nullptr;
    allocInfo.commandPool = commandPool;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = (uint32_t)numBuffers;

    CHECK_VK(vkAllocateCommandBuffers(device, &allocInfo, commandBuffers.data()), "Failed to allocate command buffers.");
}

void VK_Device::recordCommandBuffers(VK_Renderpass* renderpass, VK_Framebuffers* framebuffers, VK_Pipeline* pipeline,VK_Buffer* vertexBuffer){
    for (size_t i = 0; i < commandBuffers.size(); i++) {
        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.pNext = nullptr;
        beginInfo.flags = 0; // Optional
        beginInfo.pInheritanceInfo = nullptr; // Optional
        CHECK_VK(vkBeginCommandBuffer(commandBuffers[i], &beginInfo), "Failed to begin recording command buffer.");

        VkRenderPassBeginInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.pNext = nullptr;
        renderPassInfo.renderPass = renderpass->getRenderpass();
        renderPassInfo.framebuffer = framebuffers->getFramebuffer(i);
        renderPassInfo.renderArea.offset = { 0, 0 };
        renderPassInfo.renderArea.extent = { surfaceData.swapchainWidth, surfaceData.swapchainHeight };
        VkClearValue clearColor = { 0.0f, 0.0f, 0.0f, 1.0f };
        renderPassInfo.clearValueCount = 1;
        renderPassInfo.pClearValues = &clearColor;
        vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

        vkCmdBindPipeline(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline->getPipeline());

        VkBuffer vertexBuffers[] = { vertexBuffer->getBuffer() };
        VkDeviceSize offsets[] = { 0 };
        vkCmdBindVertexBuffers(commandBuffers[i], 0, 1, vertexBuffers, offsets);

        vkCmdDraw(commandBuffers[i], 3, 1, 0, 0);

        vkCmdEndRenderPass(commandBuffers[i]);

        CHECK_VK(vkEndCommandBuffer(commandBuffers[i]), "Failed to end recording command buffer.");
    }
}

uint32_t VK_Device::findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties){
    for (uint32_t i = 0; i < deviceData.deviceMemoryProperties.memoryTypeCount; i++) {
        if ((typeFilter & (1 << i)) && (deviceData.deviceMemoryProperties.memoryTypes[i].propertyFlags & properties) == properties) {
            return i;
        }
    }

    CHECK_VK(VK_ERROR_OUT_OF_DEVICE_MEMORY,"Failed to find memory type.");
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