#include "VK_CompatibilityChecks.h"

#include "renderSystem/RenderSystem.h"

namespace Fierce {

    bool VK_Check_Device_General::check(ExtensionValidationLayerData* data1, DeviceData* data2, SurfaceData* data3) {
        if (data2->deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
            RenderSystem::RenderSystem::LOGGER->info("General check passed for device %s.",data2->deviceProperties.deviceName);
            return true;
        }
        else {
            RenderSystem::LOGGER->warn("General check failed for device %s.", data2->deviceProperties.deviceName);
            return false;
        }
    }

    bool VK_Check_Device_Queues::check(ExtensionValidationLayerData* data1, DeviceData* data2, SurfaceData* data3) {
        int i = 0;

        //Look for dedicated transfer queue
        for (VkQueueFamilyProperties queueFamily : data2->queueFamilies) {
            if (!(queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) && (queueFamily.queueFlags & VK_QUEUE_TRANSFER_BIT)) {
                data2->transferQueueIndex = i;
                data2->hasDedicatedTransferQueue = true;
                RenderSystem::LOGGER->info("Found dedicated transfer queue: %i",i);
                break;
            }
            i++;
        }

        //Look for graphics queue
        i = 0;
        if (data2->hasDedicatedTransferQueue) {
            for (VkQueueFamilyProperties queueFamily : data2->queueFamilies) {
                bool presentSupport = data2->presentSupport[i];
                if ((queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) && presentSupport) {
                    RenderSystem::LOGGER->info("Found graphics queue: %i", i);
                    data2->graphicsQueueIndex = i;
                    RenderSystem::LOGGER->info("Queue check passed for device %s.", data2->deviceProperties.deviceName);
                    return true;
                }
                i++;
            }
        }

        //Look for graphics and transfer queue
        else {
            for (VkQueueFamilyProperties queueFamily : data2->queueFamilies) {
                bool presentSupport = data2->presentSupport[i];
                if ((queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) && (queueFamily.queueFlags & VK_QUEUE_TRANSFER_BIT) && presentSupport) {
                    RenderSystem::LOGGER->info("Found graphics and transfer queue: %i", i);
                    data2->transferQueueIndex = i;
                    data2->graphicsQueueIndex = i;
                    RenderSystem::LOGGER->info("Queue check passed for device %s.", data2->deviceProperties.deviceName);
                    return true;
                }
                i++;
            }
        }

        RenderSystem::LOGGER->warn("Queue check failed for device %s.", data2->deviceProperties.deviceName);
        return false;
    }

    bool VK_Check_Device_Extensions::check(ExtensionValidationLayerData* data1, DeviceData* data2, SurfaceData* data3) {
        for (const auto& extension : m_extensions) {
            if (isExtensionSupported(extension, &(data1->supportedExtensions))) {
                data1->enabledExtensions.push_back(extension);
            }
            else {
                if (m_required) {
                    RenderSystem::LOGGER->warn("Required extension %s is not supported.", extension);
                    return false;
                }
                else {
                    RenderSystem::LOGGER->warn("Desired extension %s is not supported.", extension);
                }
            }
        }

        RenderSystem::LOGGER->info("Extension check passed.");
        return true;
    }

    bool VK_Check_Device_Extensions::isExtensionSupported(const char* extensionName, std::vector<VkExtensionProperties>* supportedExtensions) {
        for (const auto& extension : *supportedExtensions) {
            if (strcmp(extension.extensionName, extensionName) == 0) {
                return true;
            }
        }
        return false;
    }

    bool VK_Check_Device_ValidationLayers::check(ExtensionValidationLayerData* data1, DeviceData* data2, SurfaceData* data3) {
        for (const auto& layer : m_layers) {
            if (isValidationLayerSupported(layer, &(data1->supportedValidationLayers))) {
                data1->enabledValidationLayers.push_back(layer);
            }
            else {
                if (m_required) {
                    RenderSystem::LOGGER->warn("Required validation layer %s is not supported.", layer);
                    return false;
                }
                else {
                    RenderSystem::LOGGER->warn("Desired validation layer %s is not supported.", layer);
                }
            }
        }

        RenderSystem::LOGGER->info("Validation layer check passed.");
        return true;
    }

    bool VK_Check_Device_ValidationLayers::isValidationLayerSupported(const char* layerName, std::vector<VkLayerProperties>* supportedLayers) {
        for (const auto& layer : *supportedLayers) {
            if (strcmp(layer.layerName, layerName) == 0) {
                return true;
            }
        }
        return false;
    }

    bool VK_Check_Device_Surface_Format::check(ExtensionValidationLayerData* data1, DeviceData* data2, SurfaceData* data3) {
        for (const auto& desiredFormat : m_formats) {
            for (const auto& availableFormat : data3->surfaceFormats) {
                if (availableFormat.format == desiredFormat) {
                    data3->swapchainFormat = availableFormat;
                    RenderSystem::LOGGER->info("Surface check passed for device %s.", data2->deviceProperties.deviceName);
                    return true;
                }
            }
        }

        RenderSystem::LOGGER->warn("Surface check failed for device %s.", data2->deviceProperties.deviceName);
        return false;
    }

    bool VK_Check_Device_Surface_PresentMode::check(ExtensionValidationLayerData* data1, DeviceData* data2, SurfaceData* data3) {
        for (const auto& desiredMode : m_presentModes) {
            for (const auto& availableMode : data3->presentModes) {
                if (availableMode == desiredMode) {
                    data3->swapchainPresentMode = desiredMode;
                    RenderSystem::LOGGER->info("Present mode check passed for device %s.", data2->deviceProperties.deviceName);
                    return true;
                }
            }
        }

        RenderSystem::LOGGER->warn("Present mode check failed for device %s.", data2->deviceProperties.deviceName);
        return false;
    }

    bool VK_Check_Sampler_Anisotropy ::check(ExtensionValidationLayerData* data1, DeviceData* data2, SurfaceData* data3) {
        if (data2->supportedDeviceFeatures.samplerAnisotropy==VK_TRUE) {
            data2->enabledDeviceFeatures.samplerAnisotropy = VK_TRUE;
        }
        RenderSystem::LOGGER->info("Sampler anisotropy check passed for device %s.", data2->deviceProperties.deviceName);
        return true;
    }

}//end namespace