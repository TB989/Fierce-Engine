#pragma once

#include "src/VulkanRenderer/renderSystem/RenderSystem.h"

namespace Fierce {

    class VK_Helper_Extensions_ValidationLayers {
    public:
        static void printExtensions(bool isInstance, std::string type, std::vector<VkExtensionProperties>* extensions) {
            RenderSystem::LOGGER->info("### Number of %s %s extensions: %i ###", type.c_str(), isInstance ? "instance" : "device", extensions->size());
            for (const auto& extension : *extensions) {
                RenderSystem::LOGGER->info("\t%s", extension.extensionName);
            }
        }

        static void printExtensions(bool isInstance, std::string type, std::vector<const char*>* extensions) {
            RenderSystem::LOGGER->info("### Number of %s %s extensions: %i ###", type.c_str(), isInstance ? "instance" : "device", extensions->size());
            for (const auto& extension : *extensions) {
                RenderSystem::LOGGER->info("\t%s", extension);
            }
        }

        static void printValidationLayers(bool isInstance, std::string type, std::vector<VkLayerProperties>* layers) {
            RenderSystem::LOGGER->info("### Number of %s %s validation layers: %i ###", type.c_str(), isInstance ? "instance" : "device", layers->size());
            for (const auto& layer : *layers) {
                RenderSystem::LOGGER->info("\t%s", layer.layerName);
            }
        }

        static void printValidationLayers(bool isInstance, std::string type, std::vector<const char*>* layers) {
            RenderSystem::LOGGER->info("### Number of %s %s validation layers: %i ###", type.c_str(), isInstance ? "instance" : "device", layers->size());
            for (const auto& layer : *layers) {
                RenderSystem::LOGGER->info("\t%s", layer);
            }
        }

        static void getExtensions(VkPhysicalDevice physicalDevice, std::vector<VkExtensionProperties>* extensions) {
            uint32_t extensionCount = 0;
            if (physicalDevice == nullptr) {
                if (vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr)!=VK_SUCCESS) {
                    RenderSystem::LOGGER->error("Failed to enumerate instance extensions.");
                }
                extensions->resize(extensionCount);
                if (vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions->data())!=VK_SUCCESS) {
                    RenderSystem::LOGGER->error("Failed to enumerate instance extensions.");
                }
            }
            else {
                if (vkEnumerateDeviceExtensionProperties(physicalDevice,nullptr, &extensionCount, nullptr) != VK_SUCCESS) {
                    RenderSystem::LOGGER->error("Failed to enumerate device extensions.");
                }
                extensions->resize(extensionCount);
                if (vkEnumerateDeviceExtensionProperties(physicalDevice,nullptr, &extensionCount, extensions->data()) != VK_SUCCESS) {
                    RenderSystem::LOGGER->error("Failed to enumerate device extensions.");
                }
            }
        }

        static bool isExtensionSupported(const char* extensionName, std::vector<VkExtensionProperties>* supportedExtensions) {
            for (const auto& extension : *supportedExtensions) {
                if (strcmp(extension.extensionName, extensionName) == 0) {
                    return true;
                }
            }
            return false;
        }

        static bool isExtensionSupported(const char* extensionName, std::vector<const char*>* supportedExtensions) {
            for (const auto& extension : *supportedExtensions) {
                if (strcmp(extension, extensionName) == 0) {
                    return true;
                }
            }
            return false;
        }

        static void checkExtensionSupport(std::vector<VkExtensionProperties>* supportedExtensions, std::vector<const char*>* enabledExtensions, std::vector<const char*>* requiredExtensions, std::vector<const char*>* desiredExtensions) {
            for (const auto& extension : *requiredExtensions) {
                if (isExtensionSupported(extension, supportedExtensions)) {
                    enabledExtensions->push_back(extension);
                }
                else {
                    RenderSystem::LOGGER->error("Required extension %s is not supported.", extension);
                }
            }

            for (const auto& extension : *desiredExtensions) {
                if (isExtensionSupported(extension, supportedExtensions)) {
                    enabledExtensions->push_back(extension);
                }
                else {
                    RenderSystem::LOGGER->warn("Desired extension %s is not supported.", extension);
                }
            }
        }

        static void getValidationLayers(VkPhysicalDevice physicalDevice, std::vector<VkLayerProperties>* layers) {
            uint32_t layerCount = 0;
            if (physicalDevice == nullptr) {
                if (vkEnumerateInstanceLayerProperties(&layerCount, nullptr)!=VK_SUCCESS) {
                    RenderSystem::LOGGER->error("Failed to enumerate instance validation layers.");
                }
                layers->resize(layerCount);
                if (vkEnumerateInstanceLayerProperties(&layerCount, layers->data()) != VK_SUCCESS) {
                    RenderSystem::LOGGER->error("Failed to enumerate instance validation layers.");
                }
            }
            else {
                if (vkEnumerateDeviceLayerProperties(physicalDevice,&layerCount, nullptr) != VK_SUCCESS) {
                    RenderSystem::LOGGER->error("Failed to enumerate instance validation layers.");
                }
                layers->resize(layerCount);
                if (vkEnumerateDeviceLayerProperties(physicalDevice,&layerCount, layers->data()) != VK_SUCCESS) {
                    RenderSystem::LOGGER->error("Failed to enumerate instance validation layers.");
                }
            }
        }

        static bool isValidationLayerSupported(const char* valiationLayerName, std::vector<VkLayerProperties>* supportedLayers) {
            for (const auto& layer : *supportedLayers) {
                if (strcmp(layer.layerName, valiationLayerName) == 0) {
                    return true;
                }
            }
            return false;
        }

        static bool isValidationLayerSupported(const char* validationLayerName, std::vector<const char*>* supportedLayers) {
            for (const auto& layer : *supportedLayers) {
                if (strcmp(layer, validationLayerName) == 0) {
                    return true;
                }
            }
            return false;
        }

        static void checkValidationLayerSupport(std::vector<VkLayerProperties>* supportedLayers, std::vector<const char*>* enabledLayers, std::vector<const char*>* requiredLayers, std::vector<const char*>* desiredLayers) {
            for (const auto& layer : *requiredLayers) {
                if (isValidationLayerSupported(layer, supportedLayers)) {
                    enabledLayers->push_back(layer);
                }
                else {
                    RenderSystem::LOGGER->error("Required validation layer %s is not supported.", layer);
                }
            }

            for (const auto& layer : *desiredLayers) {
                if (isValidationLayerSupported(layer, supportedLayers)) {
                    enabledLayers->push_back(layer);
                }
                else {
                    RenderSystem::LOGGER->warn("Desired validation layer %s is not supported.", layer);
                }
            }
        }

    };

}