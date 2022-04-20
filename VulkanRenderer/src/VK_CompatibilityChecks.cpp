#include "VK_CompatibilityChecks.h"

#include "Main.h"

bool VK_Check_Device_General::check(ExtensionValidationLayerData* data1, DeviceData* data2,SurfaceData* data3){
    if (data2->deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
        Main::LOGGER->info("General check passed.");
        return true;
    }
    else {
        Main::LOGGER->error("General check failed.");
        return false;
    }
}

bool VK_Check_Device_Queues::check(ExtensionValidationLayerData* data1, DeviceData* data2, SurfaceData* data3){
    int i = 0;
    for (VkQueueFamilyProperties queueFamily : data2->queueFamilies) {
        bool presentSupport = data2->presentSupport[i];
        if ((queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) && (queueFamily.queueFlags & VK_QUEUE_TRANSFER_BIT) &&presentSupport) {
            data2->transferQueueIndex = i;
            data2->graphicsQueueIndex = i;
            Main::LOGGER->info("Queue check passed.");
            return true;
        }
        i++;
    }

    Main::LOGGER->error("Queue check failed.");
    return false;
}

bool VK_Check_Device_Extensions::check(ExtensionValidationLayerData* data1, DeviceData* data2, SurfaceData* data3){
    for (const auto& extension : m_extensions) {
        if (isExtensionSupported(extension, &(data1->supportedExtensions))) {
            data1->enabledExtensions.push_back(extension);
        }
        else {
            if (m_required) {
                Main::LOGGER->warn("Required extension %s is not supported.", extension);
                return false;
            }
            else {
                Main::LOGGER->warn("Desired extension %s is not supported.", extension);
            }
        }
    }

    Main::LOGGER->info("Extension check passed.");
    return true;
}

bool VK_Check_Device_Extensions::isExtensionSupported(const char* extensionName, std::vector<VkExtensionProperties>* supportedExtensions){
    for (const auto& extension : *supportedExtensions) {
        if (strcmp(extension.extensionName, extensionName) == 0) {
            return true;
        }
    }
    return false;
}

bool VK_Check_Device_ValidationLayers::check(ExtensionValidationLayerData* data1, DeviceData* data2, SurfaceData* data3){
    for (const auto& layer : m_layers) {
        if (isValidationLayerSupported(layer, &(data1->supportedValidationLayers))) {
            data1->enabledValidationLayers.push_back(layer);
        }
        else {
            if (m_required) {
                Main::LOGGER->warn("Required validation layer %s is not supported.", layer);
                return false;
            }
            else {
                Main::LOGGER->warn("Desired validation layer %s is not supported.", layer);
            }
        }
    }

    Main::LOGGER->info("Validation layer check passed.");
    return true;
}

bool VK_Check_Device_ValidationLayers::isValidationLayerSupported(const char* layerName, std::vector<VkLayerProperties>* supportedLayers){
    for (const auto& layer : *supportedLayers) {
        if (strcmp(layer.layerName, layerName) == 0) {
            return true;
        }
    }
    return false;
}

bool VK_Check_Device_Surface_Format::check(ExtensionValidationLayerData* data1,DeviceData* data2, SurfaceData* data3){
    //m_formats.push_back(VK_FORMAT_B8G8R8A8_SRGB);
    for (const auto& desiredFormat : m_formats) {
        for (const auto& availableFormat : data3->surfaceFormats) {
            if (availableFormat.format == desiredFormat) {
                data3->swapchainFormat = availableFormat;
                Main::LOGGER->info("Surface check passed.");
                return true;
            }
        }
    }

    Main::LOGGER->warn("Surface check failed.");
    return false;
}

bool VK_Check_Device_Surface_PresentMode::check(ExtensionValidationLayerData* data1, DeviceData* data2, SurfaceData* data3){
    m_presentModes.push_back(VK_PRESENT_MODE_MAILBOX_KHR);
    for (const auto& desiredMode : m_presentModes) {
        for (const auto& availableMode : data3->presentModes) {
            if (availableMode == desiredMode) {
                data3->swapchainPresentMode = desiredMode;
                Main::LOGGER->info("Present mode check passed.");
                return true;
            }
        }
    }

    Main::LOGGER->warn("Present mode check failed.");
    return false;
}
