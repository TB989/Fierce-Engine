#include "VK_CompatibilityChecks.h"

bool VK_Check_Device_General::check(ExtensionValidationLayerData* data1, DeviceData* data2,SurfaceData* data3){
    if (data2->deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
        LOGGER->info("\t#General check passed.");
        return true;
    }
    else {
        LOGGER->warn("\t#General check failed.");
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
            LOGGER->info("\t#Queue check passed.");
            return true;
        }
        i++;
    }

    LOGGER->warn("\t#Queue check failed.");
    return false;
}

bool VK_Check_Device_Extensions::check(ExtensionValidationLayerData* data1, DeviceData* data2, SurfaceData* data3){
    for (const auto& extension : m_extensions) {
        if (isExtensionSupported(extension, &(data1->supportedExtensions))) {
            data1->enabledExtensions.push_back(extension);
            LOGGER->info("\t#Extension check passed for extension %s.", extension);
        }
        else {
            if (m_required) {
                LOGGER->warn("\t#Required extension %s is not supported.", extension);
                return false;
            }
            else {
                LOGGER->warn("\t#Desired extension %s is not supported.", extension);
            }
        }
    }

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
            LOGGER->info("\t#Validation layer check passed for layer %s.",layer);
        }
        else {
            if (m_required) {
                LOGGER->warn("\t#Required validation layer %s is not supported.", layer);
                return false;
            }
            else {
                LOGGER->warn("\t#Desired validation layer %s is not supported.", layer);
            }
        }
    }

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
    for (const auto& desiredFormat : m_formats) {
        for (const auto& availableFormat : data3->surfaceFormats) {
            if (availableFormat.format == desiredFormat) {
                data3->swapchainFormat = availableFormat;
                LOGGER->info("\t#Surface check passed.");
                return true;
            }
        }
    }

    LOGGER->warn("\t#Surface check failed.");
    return false;
}

bool VK_Check_Device_Surface_PresentMode::check(ExtensionValidationLayerData* data1, DeviceData* data2, SurfaceData* data3){
    for (const auto& desiredMode : m_presentModes) {
        for (const auto& availableMode : data3->presentModes) {
            if (availableMode == desiredMode) {
                data3->swapchainPresentMode = desiredMode;
                LOGGER->info("\t#Present mode check passed.");
                return true;
            }
        }
    }

    LOGGER->warn("\t#Present mode check failed.");
    return false;
}
