#pragma once

#include "Common.h"
#include "VulkanObject.h"

class VK_Helper_Extensions_ValidationLayers{
public:
    static void printExtensions(bool isInstance,std::string type,std::vector<VkExtensionProperties> *extensions) {
        LOGGER->info("### Number of %s %s extensions: %i ###", type.c_str(), isInstance? "instance":"device",extensions->size());
        for (const auto& extension : *extensions) {
            LOGGER->info("\t%s", extension.extensionName);
        }
    }

    static void printExtensions(bool isInstance, std::string type, std::vector<const char*> *extensions) {
        LOGGER->info("### Number of %s %s extensions: %i ###", type.c_str(), isInstance ? "instance" : "device", extensions->size());
        for (const auto& extension : *extensions) {
            LOGGER->info("\t%s", extension);
        }
    }

    static void printValidationLayers(bool isInstance, std::string type, std::vector<VkLayerProperties> *layers) {
        LOGGER->info("### Number of %s %s validation layers: %i ###", type.c_str(), isInstance ? "instance" : "device", layers->size());
        for (const auto& layer : *layers) {
            LOGGER->info("\t%s", layer.layerName);
        }
    }

    static void printValidationLayers(bool isInstance, std::string type, std::vector<const char*> *layers) {
        LOGGER->info("### Number of %s %s validation layers: %i ###", type.c_str(), isInstance ? "instance" : "device", layers->size());
        for (const auto& layer : *layers) {
            LOGGER->info("\t%s", layer);
        }
    }

    static void getExtensions(VkPhysicalDevice physicalDevice, std::vector<VkExtensionProperties> *extensions) {
        uint32_t extensionCount = 0;
        if (physicalDevice==nullptr) {
            CHECK_VK(vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr), "Failed to enumerate instance extensions.");
            extensions->resize(extensionCount);
            CHECK_VK(vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions->data()), "Failed to enumerate instance extensions.");
        }
        else {
            CHECK_VK(vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, nullptr), "Failed to enumerate device extensions.");
            extensions->resize(extensionCount);
            CHECK_VK(vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, extensions->data()), "Failed to enumerate device extensions.");
        }
    }

    static bool isExtensionSupported(const char* extensionName, std::vector<VkExtensionProperties> *supportedExtensions) {
        for (const auto& extension : *supportedExtensions) {
            if (strcmp(extension.extensionName, extensionName) == 0) {
                return true;
            }
        }
        return false;
    }

    static bool isExtensionSupported(const char* extensionName, std::vector<const char*> *supportedExtensions) {
        for (const auto& extension : *supportedExtensions) {
            if (strcmp(extension, extensionName) == 0) {
                return true;
            }
        }
        return false;
    }

    static void checkExtensionSupport(std::vector<VkExtensionProperties> *supportedExtensions, std::vector<const char*> *enabledExtensions, std::vector<const char*> *requiredExtensions,std::vector<const char*> *desiredExtensions) {
        for (const auto& extension : *requiredExtensions) {
            if (isExtensionSupported(extension,supportedExtensions)) {
                enabledExtensions->push_back(extension);
            }
            else {
                LOGGER->error("Required extension %s is not supported.", extension);
                CHECK_VK(VK_ERROR_EXTENSION_NOT_PRESENT, "Required extensions are not supported.");
            }
        }

        for (const auto& extension : *desiredExtensions) {
            if (isExtensionSupported(extension,supportedExtensions)) {
                enabledExtensions->push_back(extension);
            }
            else {
                LOGGER->warn("Desired extension %s is not supported.", extension);
            }
        }
    }

    static void getValidationLayers(VkPhysicalDevice physicalDevice, std::vector<VkLayerProperties> *layers) {
        uint32_t layerCount = 0;
        if (physicalDevice==nullptr) {
            CHECK_VK(vkEnumerateInstanceLayerProperties(&layerCount, nullptr), "Failed to enumerate instance validation layers.");
            layers->resize(layerCount);
            CHECK_VK(vkEnumerateInstanceLayerProperties(&layerCount, layers->data()), "Failed to enumerate instance validation layers.");
        }
        else {
            CHECK_VK(vkEnumerateDeviceLayerProperties(physicalDevice, &layerCount, nullptr), "Failed to enumerate device validation layers.");
            layers->resize(layerCount);
            CHECK_VK(vkEnumerateDeviceLayerProperties(physicalDevice, &layerCount, layers->data()), "Failed to enumerate device validation layers.");
        }
    }

    static bool isValidationLayerSupported(const char* valiationLayerName, std::vector<VkLayerProperties> *supportedLayers) {
        for (const auto& layer : *supportedLayers) {
            if (strcmp(layer.layerName, valiationLayerName) == 0) {
                return true;
            }
        }
        return false;
    }

    static bool isValidationLayerSupported(const char* validationLayerName, std::vector<const char*> *supportedLayers) {
        for (const auto& layer : *supportedLayers) {
            if (strcmp(layer, validationLayerName) == 0) {
                return true;
            }
        }
        return false;
    }

    static void checkValidationLayerSupport(std::vector<VkLayerProperties> *supportedLayers, std::vector<const char*> *enabledLayers, std::vector<const char*> *requiredLayers, std::vector<const char*> *desiredLayers) {
        for (const auto& layer : *requiredLayers) {
            if (isValidationLayerSupported(layer, supportedLayers)) {
                enabledLayers->push_back(layer);
            }
            else {
                LOGGER->error("Required validation layer %s is not supported.", layer);
                CHECK_VK(VK_ERROR_EXTENSION_NOT_PRESENT, "Required valiation layers are not supported.");
            }
        }

        for (const auto& layer : *desiredLayers) {
            if (isValidationLayerSupported(layer, supportedLayers)) {
                enabledLayers->push_back(layer);
            }
            else {
                LOGGER->warn("Desired validation layer %s is not supported.", layer);
            }
        }
    }

};