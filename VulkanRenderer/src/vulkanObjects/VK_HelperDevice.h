#pragma once

#include "vulkan/vulkan.h"

#include "renderSystem/RenderSystem.h"

#include "VK_CompatibilityChecks.h"

#include <vector>

namespace Fierce {

    class VK_Helper_Device {
    public:
        static void getAllPhysicalDevices(VkInstance instance, std::vector<VkPhysicalDevice>* devices) {
            uint32_t deviceCount = 0;
            vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
            if (deviceCount == 0) {
                RenderSystem::LOGGER->error("No graphics card with vulkan support found.");
            }
            devices->resize(deviceCount);
            vkEnumeratePhysicalDevices(instance, &deviceCount, devices->data());
        }

        static void getDeviceData(VkPhysicalDevice device, VkSurfaceKHR surface, DeviceData* data) {
            vkGetPhysicalDeviceProperties(device, &data->deviceProperties);
            vkGetPhysicalDeviceFeatures(device, &data->supportedDeviceFeatures);
            vkGetPhysicalDeviceMemoryProperties(device, &data->deviceMemoryProperties);
            uint32_t queueFamilyCount = 0;
            vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
            data->queueFamilies.resize(queueFamilyCount);
            vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, data->queueFamilies.data());

            data->presentSupport.clear();
            data->presentSupport.resize(queueFamilyCount);
            for (uint32_t i = 0; i < queueFamilyCount; i++) {
                VkBool32 supported;
                vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &supported);

                if (supported) {
                    data->presentSupport[i] = true;
                }
            }
        }

        static void getSurfaceData(VkPhysicalDevice device, VkSurfaceKHR surface, SurfaceData* data) {
            uint32_t formatCount; 
            uint32_t presentModeCount;

            if (vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &data->surfaceCapabilities)!=VK_SUCCESS) {
                RenderSystem::LOGGER->error("Failed to get surface capabilities.");
            }

            if (vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr) != VK_SUCCESS) {
                RenderSystem::LOGGER->error("Failed to get surface formats.");
            }
            data->surfaceFormats.resize(formatCount);
            if (vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, data->surfaceFormats.data()) != VK_SUCCESS) {
                RenderSystem::LOGGER->error("Failed to get surface formats.");
            }

            if (vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr) != VK_SUCCESS) {
                RenderSystem::LOGGER->error("Failed to get present modes.");
            }
            data->presentModes.resize(presentModeCount);
            if (vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, data->presentModes.data()) != VK_SUCCESS) {
                RenderSystem::LOGGER->error("Failed to get present modes.");
            }
        }

        static void printDeviceProperties(DeviceData* data) {
            std::string deviceType;
            switch (data->deviceProperties.deviceType) {
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
            RenderSystem::LOGGER->info("Device: %s (%s)", data->deviceProperties.deviceName, deviceType.c_str());
        }

        static void getSampleCounts(VkSampleCountFlags flags, std::string* samples) {
            samples->clear();
            if (flags & VK_SAMPLE_COUNT_1_BIT) {
                samples->assign("VK_SAMPLE_COUNT_1_BIT");
            }
            if (flags & VK_SAMPLE_COUNT_2_BIT) {
                samples->assign("VK_SAMPLE_COUNT_2_BIT");
            }
            if (flags & VK_SAMPLE_COUNT_4_BIT) {
                samples->assign("VK_SAMPLE_COUNT_4_BIT");
            }
            if (flags & VK_SAMPLE_COUNT_8_BIT) {
                samples->assign("VK_SAMPLE_COUNT_8_BIT");
            }
            if (flags & VK_SAMPLE_COUNT_16_BIT) {
                samples->assign("VK_SAMPLE_COUNT_16_BIT");
            }
            if (flags & VK_SAMPLE_COUNT_32_BIT) {
                samples->assign("VK_SAMPLE_COUNT_32_BIT");
            }
            if (flags & VK_SAMPLE_COUNT_64_BIT) {
                samples->assign("VK_SAMPLE_COUNT_64_BIT");
            }
        }

        static void printDeviceLimits(DeviceData* data) {
            std::string flags = "";
            RenderSystem::LOGGER->info("Limits:");
            RenderSystem::LOGGER->info("\tBufferImageGranularity: %llu", data->deviceProperties.limits.bufferImageGranularity);
            RenderSystem::LOGGER->info("\tDiscreteQueuePriorities: %lu", data->deviceProperties.limits.discreteQueuePriorities);
            getSampleCounts(data->deviceProperties.limits.framebufferColorSampleCounts, &flags);
            RenderSystem::LOGGER->info("\tFramebufferColorSampleCounts: %s", flags.c_str());
            getSampleCounts(data->deviceProperties.limits.framebufferDepthSampleCounts, &flags);
            RenderSystem::LOGGER->info("\tFramebufferDepthSampleCounts: %s", flags.c_str());
            getSampleCounts(data->deviceProperties.limits.framebufferNoAttachmentsSampleCounts, &flags);
            RenderSystem::LOGGER->info("\tFramebufferNoAttachmentsSampleCounts: %s", flags.c_str());
            getSampleCounts(data->deviceProperties.limits.framebufferStencilSampleCounts, &flags);
            RenderSystem::LOGGER->info("\tFramebufferStencilSampleCounts: %s", flags.c_str());
            RenderSystem::LOGGER->info("\tLineWidthGranularity: %1.3f", data->deviceProperties.limits.lineWidthGranularity);
            RenderSystem::LOGGER->info("\tLineWidthRange: %1.3f", data->deviceProperties.limits.lineWidthRange);
            RenderSystem::LOGGER->info("\tMaxBoundDescriptorSets: %lu", data->deviceProperties.limits.maxBoundDescriptorSets);
            RenderSystem::LOGGER->info("\tMaxClipDistances: %lu", data->deviceProperties.limits.maxClipDistances);
            RenderSystem::LOGGER->info("\tMaxColorAttachments: %lu", data->deviceProperties.limits.maxColorAttachments);
            RenderSystem::LOGGER->info("\tMaxCombinedClipAndCullDistances: %lu", data->deviceProperties.limits.maxCombinedClipAndCullDistances);
            RenderSystem::LOGGER->info("\tMaxComputeSharedMemorySize: %lu", data->deviceProperties.limits.maxComputeSharedMemorySize);
            RenderSystem::LOGGER->info("\tMaxComputeWorkGroupCount: %lu", data->deviceProperties.limits.maxComputeWorkGroupCount);
            RenderSystem::LOGGER->info("\tMaxComputeWorkGroupInvocations: %lu", data->deviceProperties.limits.maxComputeWorkGroupInvocations);
            RenderSystem::LOGGER->info("\tMaxComputeWorkGroupSize: %lu", data->deviceProperties.limits.maxComputeWorkGroupSize);
            RenderSystem::LOGGER->info("\tMaxCullDistances: %lu", data->deviceProperties.limits.maxCullDistances);
            RenderSystem::LOGGER->info("\tMaxDescriptorSetInputAttachments: %lu", data->deviceProperties.limits.maxDescriptorSetInputAttachments);
            RenderSystem::LOGGER->info("\tMaxDescriptorSetSampledImages: %lu", data->deviceProperties.limits.maxDescriptorSetSampledImages);
            RenderSystem::LOGGER->info("\tMaxDescriptorSetSamplers: %lu", data->deviceProperties.limits.maxDescriptorSetSamplers);
            RenderSystem::LOGGER->info("\tMaxDescriptorSetStorageBuffers: %lu", data->deviceProperties.limits.maxDescriptorSetStorageBuffers);
            RenderSystem::LOGGER->info("\tMaxDescriptorSetStorageBuffersDynamic: %lu", data->deviceProperties.limits.maxDescriptorSetStorageBuffersDynamic);
            RenderSystem::LOGGER->info("\tMaxDescriptorSetStorageImages: %lu", data->deviceProperties.limits.maxDescriptorSetStorageImages);
            RenderSystem::LOGGER->info("\tMaxDescriptorSetUniformBuffers: %lu", data->deviceProperties.limits.maxDescriptorSetUniformBuffers);
            RenderSystem::LOGGER->info("\tMaxDescriptorSetUniformBuffersDynamic: %lu", data->deviceProperties.limits.maxDescriptorSetUniformBuffersDynamic);
            RenderSystem::LOGGER->info("\tMaxDrawIndexedIndexValue: %lu", data->deviceProperties.limits.maxDrawIndexedIndexValue);
            RenderSystem::LOGGER->info("\tMaxDrawIndirectCount: %lu", data->deviceProperties.limits.maxDrawIndirectCount);
            RenderSystem::LOGGER->info("\tMaxFragmentCombinedOutputResources: %lu", data->deviceProperties.limits.maxFragmentCombinedOutputResources);
            RenderSystem::LOGGER->info("\tMaxFragmentDualSrcAttachments: %lu", data->deviceProperties.limits.maxFragmentDualSrcAttachments);
            RenderSystem::LOGGER->info("\tMaxFragmentInputComponents: %lu", data->deviceProperties.limits.maxFragmentInputComponents);
            RenderSystem::LOGGER->info("\tMaxFragmentOutputAttachments: %lu", data->deviceProperties.limits.maxFragmentOutputAttachments);
            RenderSystem::LOGGER->info("\tMaxFramebufferHeight: %lu", data->deviceProperties.limits.maxFramebufferHeight);
            RenderSystem::LOGGER->info("\tMaxFramebufferLayers: %lu", data->deviceProperties.limits.maxFramebufferLayers);
            RenderSystem::LOGGER->info("\tMaxFramebufferWidth: %lu", data->deviceProperties.limits.maxFramebufferWidth);
            RenderSystem::LOGGER->info("\tMaxGeometryInputComponents: %lu", data->deviceProperties.limits.maxGeometryInputComponents);
            RenderSystem::LOGGER->info("\tMaxGeometryOutputComponents: %lu", data->deviceProperties.limits.maxGeometryOutputComponents);
            RenderSystem::LOGGER->info("\tMaxGeometryOutputVertices: %lu", data->deviceProperties.limits.maxGeometryOutputVertices);
            RenderSystem::LOGGER->info("\tMaxGeometryShaderInvocations: %lu", data->deviceProperties.limits.maxGeometryShaderInvocations);
            RenderSystem::LOGGER->info("\tMaxGeometryTotalOutputComponents: %lu", data->deviceProperties.limits.maxGeometryTotalOutputComponents);
            RenderSystem::LOGGER->info("\tMaxImageArrayLayers: %lu", data->deviceProperties.limits.maxImageArrayLayers);
            RenderSystem::LOGGER->info("\tMaxImageDimension1D: %lu", data->deviceProperties.limits.maxImageDimension1D);
            RenderSystem::LOGGER->info("\tMaxImageDimension2D: %lu", data->deviceProperties.limits.maxImageDimension2D);
            RenderSystem::LOGGER->info("\tMaxImageDimension3D: %lu", data->deviceProperties.limits.maxImageDimension3D);
            RenderSystem::LOGGER->info("\tMaxImageDimensionCube: %lu", data->deviceProperties.limits.maxImageDimensionCube);
            RenderSystem::LOGGER->info("\tMaxInterpolationOffset: %1.3f", data->deviceProperties.limits.maxInterpolationOffset);
            RenderSystem::LOGGER->info("\tMaxMemoryAllocationCount: %lu", data->deviceProperties.limits.maxMemoryAllocationCount);
            RenderSystem::LOGGER->info("\tMaxPerStageDescriptorInputAttachments: %lu", data->deviceProperties.limits.maxPerStageDescriptorInputAttachments);
            RenderSystem::LOGGER->info("\tMaxPerStageDescriptorSampledImages: %lu", data->deviceProperties.limits.maxPerStageDescriptorSampledImages);
            RenderSystem::LOGGER->info("\tMaxPerStageDescriptorSamplers: %lu", data->deviceProperties.limits.maxPerStageDescriptorSamplers);
            RenderSystem::LOGGER->info("\tMaxPerStageDescriptorStorageBuffers: %lu", data->deviceProperties.limits.maxPerStageDescriptorStorageBuffers);
            RenderSystem::LOGGER->info("\tMaxPerStageDescriptorStorageImages: %lu", data->deviceProperties.limits.maxPerStageDescriptorStorageImages);
            RenderSystem::LOGGER->info("\tMaxPerStageDescriptorUniformBuffers: %lu", data->deviceProperties.limits.maxPerStageDescriptorUniformBuffers);
            RenderSystem::LOGGER->info("\tMaxPerStageResources: %lu", data->deviceProperties.limits.maxPerStageResources);
            RenderSystem::LOGGER->info("\tMaxPushConstantsSize: %lu", data->deviceProperties.limits.maxPushConstantsSize);
            RenderSystem::LOGGER->info("\tMaxSampleMaskWords: %lu", data->deviceProperties.limits.maxSampleMaskWords);
            RenderSystem::LOGGER->info("\tMaxSamplerAllocationCount: %lu", data->deviceProperties.limits.maxSamplerAllocationCount);
            RenderSystem::LOGGER->info("\tMaxSamplerAnisotropy: %1.3f", data->deviceProperties.limits.maxSamplerAnisotropy);
            RenderSystem::LOGGER->info("\tMaxSamplerLodBias: %1.3f", data->deviceProperties.limits.maxSamplerLodBias);
            RenderSystem::LOGGER->info("\tMaxStorageBufferRange: %lu", data->deviceProperties.limits.maxStorageBufferRange);
            RenderSystem::LOGGER->info("\tMaxTessellationControlPerPatchOutputComponents: %lu", data->deviceProperties.limits.maxTessellationControlPerPatchOutputComponents);
            RenderSystem::LOGGER->info("\tMaxTessellationControlPerVertexInputComponents: %lu", data->deviceProperties.limits.maxTessellationControlPerVertexInputComponents);
            RenderSystem::LOGGER->info("\tMaxTessellationControlPerVertexOutputComponents: %lu", data->deviceProperties.limits.maxTessellationControlPerVertexOutputComponents);
            RenderSystem::LOGGER->info("\tMaxTessellationControlTotalOutputComponents: %lu", data->deviceProperties.limits.maxTessellationControlTotalOutputComponents);
            RenderSystem::LOGGER->info("\tMaxTessellationEvaluationInputComponents: %lu", data->deviceProperties.limits.maxTessellationEvaluationInputComponents);
            RenderSystem::LOGGER->info("\tMaxTessellationEvaluationOutputComponents: %lu", data->deviceProperties.limits.maxTessellationEvaluationOutputComponents);
            RenderSystem::LOGGER->info("\tMaxTessellationGenerationLevel: %lu", data->deviceProperties.limits.maxTessellationGenerationLevel);
            RenderSystem::LOGGER->info("\tMaxTessellationPatchSize: %lu", data->deviceProperties.limits.maxTessellationPatchSize);
            RenderSystem::LOGGER->info("\tMaxTexelBufferElements: %lu", data->deviceProperties.limits.maxTexelBufferElements);
            RenderSystem::LOGGER->info("\tMaxTexelGatherOffset: %lu", data->deviceProperties.limits.maxTexelGatherOffset);
            RenderSystem::LOGGER->info("\tMaxTexelOffset: %lu", data->deviceProperties.limits.maxTexelOffset);
            RenderSystem::LOGGER->info("\tMaxUniformBufferRange: %lu", data->deviceProperties.limits.maxUniformBufferRange);
            RenderSystem::LOGGER->info("\tMaxVertexInputAttributeOffset: %lu", data->deviceProperties.limits.maxVertexInputAttributeOffset);
            RenderSystem::LOGGER->info("\tMaxVertexInputAttributes: %lu", data->deviceProperties.limits.maxVertexInputAttributes);
            RenderSystem::LOGGER->info("\tMaxVertexInputBindings: %lu", data->deviceProperties.limits.maxVertexInputBindings);
            RenderSystem::LOGGER->info("\tMaxVertexInputBindingStride: %lu", data->deviceProperties.limits.maxVertexInputBindingStride);
            RenderSystem::LOGGER->info("\tMaxVertexOutputComponents: %lu", data->deviceProperties.limits.maxVertexOutputComponents);
            RenderSystem::LOGGER->info("\tMaxViewportDimensions: %lu", data->deviceProperties.limits.maxViewportDimensions);
            RenderSystem::LOGGER->info("\tMaxViewports: %lu", data->deviceProperties.limits.maxViewports);
            RenderSystem::LOGGER->info("\tMinInterpolationOffset: %1.3f", data->deviceProperties.limits.minInterpolationOffset);
            RenderSystem::LOGGER->info("\tMinMemoryMapAlignment: %lu", data->deviceProperties.limits.minMemoryMapAlignment);
            RenderSystem::LOGGER->info("\tMinStorageBufferOffsetAlignment: %lu", data->deviceProperties.limits.minStorageBufferOffsetAlignment);
            RenderSystem::LOGGER->info("\tMipmapPrecisionBits: %lu", data->deviceProperties.limits.mipmapPrecisionBits);
            RenderSystem::LOGGER->info("\tNonCoherentAtomSize: %lu", data->deviceProperties.limits.nonCoherentAtomSize);
            RenderSystem::LOGGER->info("\tOptimalBufferCopyOffsetAlignment: %lu", data->deviceProperties.limits.optimalBufferCopyOffsetAlignment);
            RenderSystem::LOGGER->info("\tOptimalBufferCopyRowPitchAlignment: %lu", data->deviceProperties.limits.optimalBufferCopyRowPitchAlignment);
            RenderSystem::LOGGER->info("\tPointSizeGranularity: %1.3f", data->deviceProperties.limits.pointSizeGranularity);
            RenderSystem::LOGGER->info("\tPointSizeRange: %1.3f", data->deviceProperties.limits.pointSizeRange);
            getSampleCounts(data->deviceProperties.limits.sampledImageColorSampleCounts, &flags);
            RenderSystem::LOGGER->info("\tSampledImageColorSampleCounts: %s", flags.c_str());
            getSampleCounts(data->deviceProperties.limits.sampledImageDepthSampleCounts, &flags);
            RenderSystem::LOGGER->info("\tSampledImageDepthSampleCounts: %s", flags.c_str());
            getSampleCounts(data->deviceProperties.limits.sampledImageIntegerSampleCounts, &flags);
            RenderSystem::LOGGER->info("\tSampledImageIntegerSampleCounts: %s", flags.c_str());
            getSampleCounts(data->deviceProperties.limits.sampledImageStencilSampleCounts, &flags);
            RenderSystem::LOGGER->info("\tSampledImageStencilSampleCounts: %s", flags.c_str());
            RenderSystem::LOGGER->info("\tSparseAddressSpaceSize: %lu", data->deviceProperties.limits.sparseAddressSpaceSize);
            RenderSystem::LOGGER->info("\tStandardSampleLocations: %s", data->deviceProperties.limits.standardSampleLocations ? "true" : "false");
            getSampleCounts(data->deviceProperties.limits.storageImageSampleCounts, &flags);
            RenderSystem::LOGGER->info("\tStorageImageSampleCounts: %s", flags.c_str());
            RenderSystem::LOGGER->info("\tStrictLines: %s", data->deviceProperties.limits.strictLines ? "true" : "false");
            RenderSystem::LOGGER->info("\tSubPixelInterpolationOffsetBits: %lu", data->deviceProperties.limits.subPixelInterpolationOffsetBits);
            RenderSystem::LOGGER->info("\tSubPixelPrecisionBits: %lu", data->deviceProperties.limits.subPixelPrecisionBits);
            RenderSystem::LOGGER->info("\tSubTexelPrecisionBits: %lu", data->deviceProperties.limits.subTexelPrecisionBits);
            RenderSystem::LOGGER->info("\tTimestampComputeAndGraphics: %s", data->deviceProperties.limits.timestampComputeAndGraphics ? "true" : "false");
            RenderSystem::LOGGER->info("\tTimestampPeriod: %1.3f", data->deviceProperties.limits.timestampPeriod);
            RenderSystem::LOGGER->info("\tViewportBoundsRange: %1.3f", data->deviceProperties.limits.viewportBoundsRange);
            RenderSystem::LOGGER->info("\tViewportSubPixelBits: %lu", data->deviceProperties.limits.viewportSubPixelBits);
        }

        static void printSupportedDeviceFeatures(DeviceData* data) {
            RenderSystem::LOGGER->info("Features:");
            RenderSystem::LOGGER->info("\tAlpahToOne: %s", data->supportedDeviceFeatures.alphaToOne ? "true" : "false");
            RenderSystem::LOGGER->info("\tDepthBiasClamp: %s", data->supportedDeviceFeatures.depthBiasClamp ? "true" : "false");
            RenderSystem::LOGGER->info("\tDepthBounds: %s", data->supportedDeviceFeatures.depthBounds ? "true" : "false");
            RenderSystem::LOGGER->info("\tDepthClamp: %s", data->supportedDeviceFeatures.depthClamp ? "true" : "false");
            RenderSystem::LOGGER->info("\tDrawIndirectFirstInstance: %s", data->supportedDeviceFeatures.drawIndirectFirstInstance ? "true" : "false");
            RenderSystem::LOGGER->info("\tDualSrcBlend: %s", data->supportedDeviceFeatures.dualSrcBlend ? "true" : "false");
            RenderSystem::LOGGER->info("\tFillModeNonSolid: %s", data->supportedDeviceFeatures.fillModeNonSolid ? "true" : "false");
            RenderSystem::LOGGER->info("\tFragmentStoresAndAtomics: %s", data->supportedDeviceFeatures.fragmentStoresAndAtomics ? "true" : "false");
            RenderSystem::LOGGER->info("\tFullDrawIndexUint32: %s", data->supportedDeviceFeatures.fullDrawIndexUint32 ? "true" : "false");
            RenderSystem::LOGGER->info("\tGeometryShader: %s", data->supportedDeviceFeatures.geometryShader ? "true" : "false");
            RenderSystem::LOGGER->info("\tImageCubeArray: %s", data->supportedDeviceFeatures.imageCubeArray ? "true" : "false");
            RenderSystem::LOGGER->info("\tIndependentBlend: %s", data->supportedDeviceFeatures.independentBlend ? "true" : "false");
            RenderSystem::LOGGER->info("\tInheritedQueries: %s", data->supportedDeviceFeatures.inheritedQueries ? "true" : "false");
            RenderSystem::LOGGER->info("\tLargePoints: %s", data->supportedDeviceFeatures.largePoints ? "true" : "false");
            RenderSystem::LOGGER->info("\tLogicOp: %s", data->supportedDeviceFeatures.logicOp ? "true" : "false");
            RenderSystem::LOGGER->info("\tMultiDrawIndirect: %s", data->supportedDeviceFeatures.multiDrawIndirect ? "true" : "false");
            RenderSystem::LOGGER->info("\tMultiViewport: %s", data->supportedDeviceFeatures.multiViewport ? "true" : "false");
            RenderSystem::LOGGER->info("\tOcclusionQueryPrecise: %s", data->supportedDeviceFeatures.occlusionQueryPrecise ? "true" : "false");
            RenderSystem::LOGGER->info("\tPipelineStatisticsQuery: %s", data->supportedDeviceFeatures.pipelineStatisticsQuery ? "true" : "false");
            RenderSystem::LOGGER->info("\tRobustBufferAccess: %s", data->supportedDeviceFeatures.robustBufferAccess ? "true" : "false");
            RenderSystem::LOGGER->info("\tSamplerAnisotropy: %s", data->supportedDeviceFeatures.samplerAnisotropy ? "true" : "false");
            RenderSystem::LOGGER->info("\tSampleRateShading: %s", data->supportedDeviceFeatures.sampleRateShading ? "true" : "false");
            RenderSystem::LOGGER->info("\tShaderClipDistance: %s", data->supportedDeviceFeatures.shaderClipDistance ? "true" : "false");
            RenderSystem::LOGGER->info("\tShaderCullDistance: %s", data->supportedDeviceFeatures.shaderCullDistance ? "true" : "false");
            RenderSystem::LOGGER->info("\tShaderFloat64: %s", data->supportedDeviceFeatures.shaderFloat64 ? "true" : "false");
            RenderSystem::LOGGER->info("\tShaderImageGatherExtended: %s", data->supportedDeviceFeatures.shaderImageGatherExtended ? "true" : "false");
            RenderSystem::LOGGER->info("\tShaderInt16: %s", data->supportedDeviceFeatures.shaderInt16 ? "true" : "false");
            RenderSystem::LOGGER->info("\tShaderInt64: %s", data->supportedDeviceFeatures.shaderInt64 ? "true" : "false");
            RenderSystem::LOGGER->info("\tShaderResourceMinLod: %s", data->supportedDeviceFeatures.shaderResourceMinLod ? "true" : "false");
            RenderSystem::LOGGER->info("\tShaderResourceResidency: %s", data->supportedDeviceFeatures.shaderResourceResidency ? "true" : "false");
            RenderSystem::LOGGER->info("\tShaderSampledImageArrayDynamicIndexing: %s", data->supportedDeviceFeatures.shaderSampledImageArrayDynamicIndexing ? "true" : "false");
            RenderSystem::LOGGER->info("\tShaderStorageBufferArrayDynamicIndexing: %s", data->supportedDeviceFeatures.shaderStorageBufferArrayDynamicIndexing ? "true" : "false");
            RenderSystem::LOGGER->info("\tShaderStorageImageArrayDynamicIndexing: %s", data->supportedDeviceFeatures.shaderStorageImageArrayDynamicIndexing ? "true" : "false");
            RenderSystem::LOGGER->info("\tShaderStorageImageExtendedFormats: %s", data->supportedDeviceFeatures.shaderStorageImageExtendedFormats ? "true" : "false");
            RenderSystem::LOGGER->info("\tShaderStorageImageMultisample: %s", data->supportedDeviceFeatures.shaderStorageImageMultisample ? "true" : "false");
            RenderSystem::LOGGER->info("\tShaderStorageImageReadWithoutFormat: %s", data->supportedDeviceFeatures.shaderStorageImageReadWithoutFormat ? "true" : "false");
            RenderSystem::LOGGER->info("\tShaderStorageImageWriteWithoutFormat: %s", data->supportedDeviceFeatures.shaderStorageImageWriteWithoutFormat ? "true" : "false");
            RenderSystem::LOGGER->info("\tShaderTessellationAndGeometryPointSize: %s", data->supportedDeviceFeatures.shaderTessellationAndGeometryPointSize ? "true" : "false");
            RenderSystem::LOGGER->info("\tShaderUniformBufferArrayDynamicIndexing: %s", data->supportedDeviceFeatures.shaderUniformBufferArrayDynamicIndexing ? "true" : "false");
            RenderSystem::LOGGER->info("\tSparseBinding: %s", data->supportedDeviceFeatures.sparseBinding ? "true" : "false");
            RenderSystem::LOGGER->info("\tSparseResidency2Samples: %s", data->supportedDeviceFeatures.sparseResidency2Samples ? "true" : "false");
            RenderSystem::LOGGER->info("\tSparseResidency4Samples: %s", data->supportedDeviceFeatures.sparseResidency4Samples ? "true" : "false");
            RenderSystem::LOGGER->info("\tSparseResidency8Samples: %s", data->supportedDeviceFeatures.sparseResidency8Samples ? "true" : "false");
            RenderSystem::LOGGER->info("\tSparseResidency16Samples: %s", data->supportedDeviceFeatures.sparseResidency16Samples ? "true" : "false");
            RenderSystem::LOGGER->info("\tSparseResidencyAliased: %s", data->supportedDeviceFeatures.sparseResidencyAliased ? "true" : "false");
            RenderSystem::LOGGER->info("\tSparseResidencyBuffer: %s", data->supportedDeviceFeatures.sparseResidencyBuffer ? "true" : "false");
            RenderSystem::LOGGER->info("\tSparseResidencyImage2D: %s", data->supportedDeviceFeatures.sparseResidencyImage2D ? "true" : "false");
            RenderSystem::LOGGER->info("\tSparseResidencyImage3D: %s", data->supportedDeviceFeatures.sparseResidencyImage3D ? "true" : "false");
            RenderSystem::LOGGER->info("\tTessellationShader: %s", data->supportedDeviceFeatures.tessellationShader ? "true" : "false");
            RenderSystem::LOGGER->info("\tTextureCompressionASTC_LDR: %s", data->supportedDeviceFeatures.textureCompressionASTC_LDR ? "true" : "false");
            RenderSystem::LOGGER->info("\tTextureCompressionBC: %s", data->supportedDeviceFeatures.textureCompressionBC ? "true" : "false");
            RenderSystem::LOGGER->info("\tTextureCompressionETC2: %s", data->supportedDeviceFeatures.textureCompressionETC2 ? "true" : "false");
            RenderSystem::LOGGER->info("\tVariableMultisampleRate: %s", data->supportedDeviceFeatures.variableMultisampleRate ? "true" : "false");
            RenderSystem::LOGGER->info("\tVertexPipelineStoresAndAtomics: %s", data->supportedDeviceFeatures.vertexPipelineStoresAndAtomics ? "true" : "false");
            RenderSystem::LOGGER->info("\tWideLines: %s", data->supportedDeviceFeatures.wideLines ? "true" : "false");
        }

        static void printActiveDeviceFeatures(DeviceData* data) {
            RenderSystem::LOGGER->info("Features:");
            RenderSystem::LOGGER->info("\tAlpahToOne: %s", data->enabledDeviceFeatures.alphaToOne ? "true" : "false");
            RenderSystem::LOGGER->info("\tDepthBiasClamp: %s", data->enabledDeviceFeatures.depthBiasClamp ? "true" : "false");
            RenderSystem::LOGGER->info("\tDepthBounds: %s", data->enabledDeviceFeatures.depthBounds ? "true" : "false");
            RenderSystem::LOGGER->info("\tDepthClamp: %s", data->enabledDeviceFeatures.depthClamp ? "true" : "false");
            RenderSystem::LOGGER->info("\tDrawIndirectFirstInstance: %s", data->enabledDeviceFeatures.drawIndirectFirstInstance ? "true" : "false");
            RenderSystem::LOGGER->info("\tDualSrcBlend: %s", data->enabledDeviceFeatures.dualSrcBlend ? "true" : "false");
            RenderSystem::LOGGER->info("\tFillModeNonSolid: %s", data->enabledDeviceFeatures.fillModeNonSolid ? "true" : "false");
            RenderSystem::LOGGER->info("\tFragmentStoresAndAtomics: %s", data->enabledDeviceFeatures.fragmentStoresAndAtomics ? "true" : "false");
            RenderSystem::LOGGER->info("\tFullDrawIndexUint32: %s", data->enabledDeviceFeatures.fullDrawIndexUint32 ? "true" : "false");
            RenderSystem::LOGGER->info("\tGeometryShader: %s", data->enabledDeviceFeatures.geometryShader ? "true" : "false");
            RenderSystem::LOGGER->info("\tImageCubeArray: %s", data->enabledDeviceFeatures.imageCubeArray ? "true" : "false");
            RenderSystem::LOGGER->info("\tIndependentBlend: %s", data->enabledDeviceFeatures.independentBlend ? "true" : "false");
            RenderSystem::LOGGER->info("\tInheritedQueries: %s", data->enabledDeviceFeatures.inheritedQueries ? "true" : "false");
            RenderSystem::LOGGER->info("\tLargePoints: %s", data->enabledDeviceFeatures.largePoints ? "true" : "false");
            RenderSystem::LOGGER->info("\tLogicOp: %s", data->enabledDeviceFeatures.logicOp ? "true" : "false");
            RenderSystem::LOGGER->info("\tMultiDrawIndirect: %s", data->enabledDeviceFeatures.multiDrawIndirect ? "true" : "false");
            RenderSystem::LOGGER->info("\tMultiViewport: %s", data->enabledDeviceFeatures.multiViewport ? "true" : "false");
            RenderSystem::LOGGER->info("\tOcclusionQueryPrecise: %s", data->enabledDeviceFeatures.occlusionQueryPrecise ? "true" : "false");
            RenderSystem::LOGGER->info("\tPipelineStatisticsQuery: %s", data->enabledDeviceFeatures.pipelineStatisticsQuery ? "true" : "false");
            RenderSystem::LOGGER->info("\tRobustBufferAccess: %s", data->enabledDeviceFeatures.robustBufferAccess ? "true" : "false");
            RenderSystem::LOGGER->info("\tSamplerAnisotropy: %s", data->enabledDeviceFeatures.samplerAnisotropy ? "true" : "false");
            RenderSystem::LOGGER->info("\tSampleRateShading: %s", data->enabledDeviceFeatures.sampleRateShading ? "true" : "false");
            RenderSystem::LOGGER->info("\tShaderClipDistance: %s", data->enabledDeviceFeatures.shaderClipDistance ? "true" : "false");
            RenderSystem::LOGGER->info("\tShaderCullDistance: %s", data->enabledDeviceFeatures.shaderCullDistance ? "true" : "false");
            RenderSystem::LOGGER->info("\tShaderFloat64: %s", data->enabledDeviceFeatures.shaderFloat64 ? "true" : "false");
            RenderSystem::LOGGER->info("\tShaderImageGatherExtended: %s", data->enabledDeviceFeatures.shaderImageGatherExtended ? "true" : "false");
            RenderSystem::LOGGER->info("\tShaderInt16: %s", data->enabledDeviceFeatures.shaderInt16 ? "true" : "false");
            RenderSystem::LOGGER->info("\tShaderInt64: %s", data->enabledDeviceFeatures.shaderInt64 ? "true" : "false");
            RenderSystem::LOGGER->info("\tShaderResourceMinLod: %s", data->enabledDeviceFeatures.shaderResourceMinLod ? "true" : "false");
            RenderSystem::LOGGER->info("\tShaderResourceResidency: %s", data->enabledDeviceFeatures.shaderResourceResidency ? "true" : "false");
            RenderSystem::LOGGER->info("\tShaderSampledImageArrayDynamicIndexing: %s", data->enabledDeviceFeatures.shaderSampledImageArrayDynamicIndexing ? "true" : "false");
            RenderSystem::LOGGER->info("\tShaderStorageBufferArrayDynamicIndexing: %s", data->enabledDeviceFeatures.shaderStorageBufferArrayDynamicIndexing ? "true" : "false");
            RenderSystem::LOGGER->info("\tShaderStorageImageArrayDynamicIndexing: %s", data->enabledDeviceFeatures.shaderStorageImageArrayDynamicIndexing ? "true" : "false");
            RenderSystem::LOGGER->info("\tShaderStorageImageExtendedFormats: %s", data->enabledDeviceFeatures.shaderStorageImageExtendedFormats ? "true" : "false");
            RenderSystem::LOGGER->info("\tShaderStorageImageMultisample: %s", data->enabledDeviceFeatures.shaderStorageImageMultisample ? "true" : "false");
            RenderSystem::LOGGER->info("\tShaderStorageImageReadWithoutFormat: %s", data->enabledDeviceFeatures.shaderStorageImageReadWithoutFormat ? "true" : "false");
            RenderSystem::LOGGER->info("\tShaderStorageImageWriteWithoutFormat: %s", data->enabledDeviceFeatures.shaderStorageImageWriteWithoutFormat ? "true" : "false");
            RenderSystem::LOGGER->info("\tShaderTessellationAndGeometryPointSize: %s", data->enabledDeviceFeatures.shaderTessellationAndGeometryPointSize ? "true" : "false");
            RenderSystem::LOGGER->info("\tShaderUniformBufferArrayDynamicIndexing: %s", data->enabledDeviceFeatures.shaderUniformBufferArrayDynamicIndexing ? "true" : "false");
            RenderSystem::LOGGER->info("\tSparseBinding: %s", data->enabledDeviceFeatures.sparseBinding ? "true" : "false");
            RenderSystem::LOGGER->info("\tSparseResidency2Samples: %s", data->enabledDeviceFeatures.sparseResidency2Samples ? "true" : "false");
            RenderSystem::LOGGER->info("\tSparseResidency4Samples: %s", data->enabledDeviceFeatures.sparseResidency4Samples ? "true" : "false");
            RenderSystem::LOGGER->info("\tSparseResidency8Samples: %s", data->enabledDeviceFeatures.sparseResidency8Samples ? "true" : "false");
            RenderSystem::LOGGER->info("\tSparseResidency16Samples: %s", data->enabledDeviceFeatures.sparseResidency16Samples ? "true" : "false");
            RenderSystem::LOGGER->info("\tSparseResidencyAliased: %s", data->enabledDeviceFeatures.sparseResidencyAliased ? "true" : "false");
            RenderSystem::LOGGER->info("\tSparseResidencyBuffer: %s", data->enabledDeviceFeatures.sparseResidencyBuffer ? "true" : "false");
            RenderSystem::LOGGER->info("\tSparseResidencyImage2D: %s", data->enabledDeviceFeatures.sparseResidencyImage2D ? "true" : "false");
            RenderSystem::LOGGER->info("\tSparseResidencyImage3D: %s", data->enabledDeviceFeatures.sparseResidencyImage3D ? "true" : "false");
            RenderSystem::LOGGER->info("\tTessellationShader: %s", data->enabledDeviceFeatures.tessellationShader ? "true" : "false");
            RenderSystem::LOGGER->info("\tTextureCompressionASTC_LDR: %s", data->enabledDeviceFeatures.textureCompressionASTC_LDR ? "true" : "false");
            RenderSystem::LOGGER->info("\tTextureCompressionBC: %s", data->enabledDeviceFeatures.textureCompressionBC ? "true" : "false");
            RenderSystem::LOGGER->info("\tTextureCompressionETC2: %s", data->enabledDeviceFeatures.textureCompressionETC2 ? "true" : "false");
            RenderSystem::LOGGER->info("\tVariableMultisampleRate: %s", data->enabledDeviceFeatures.variableMultisampleRate ? "true" : "false");
            RenderSystem::LOGGER->info("\tVertexPipelineStoresAndAtomics: %s", data->enabledDeviceFeatures.vertexPipelineStoresAndAtomics ? "true" : "false");
            RenderSystem::LOGGER->info("\tWideLines: %s", data->enabledDeviceFeatures.wideLines ? "true" : "false");
        }

        static void printDeviceMemoryProperties(DeviceData* data) {
            RenderSystem::LOGGER->info("Memory properties:");
            for (uint32_t i = 0; i < data->deviceMemoryProperties.memoryHeapCount; i++) {
                RenderSystem::LOGGER->info("\tHeap %i:", i);
                RenderSystem::LOGGER->info("\tMemory size: %llu GB", data->deviceMemoryProperties.memoryHeaps[i].size / 100000000);
                std::string flags = "";
                if (data->deviceMemoryProperties.memoryHeaps[i].flags & VK_MEMORY_HEAP_DEVICE_LOCAL_BIT) {
                    flags.append(" DEVICE_LOCAL_BIT");
                }
                if (data->deviceMemoryProperties.memoryHeaps[i].flags & VK_MEMORY_HEAP_MULTI_INSTANCE_BIT) {
                    flags.append(" MULTI_INSTANCE_BIT");
                }
                RenderSystem::LOGGER->info("\tHeap flags: %s", flags.c_str());

                for (uint32_t j = 0; j < data->deviceMemoryProperties.memoryTypeCount; j++) {
                    if (data->deviceMemoryProperties.memoryTypes[j].heapIndex == i) {
                        RenderSystem::LOGGER->info("\tMemory type %i:", j);
                        std::string flags = "";
                        if (data->deviceMemoryProperties.memoryTypes[j].propertyFlags & VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT) {
                            flags.append(" DEVICE_LOCAL_BIT");
                        }
                        if (data->deviceMemoryProperties.memoryTypes[j].propertyFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) {
                            flags.append(" HOST_VISIBLE_BIT");
                        }
                        if (data->deviceMemoryProperties.memoryTypes[j].propertyFlags & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT) {
                            flags.append(" HOST_COHERENT_BIT");
                        }
                        if (data->deviceMemoryProperties.memoryTypes[j].propertyFlags & VK_MEMORY_PROPERTY_HOST_CACHED_BIT) {
                            flags.append(" HOST_CACHED_BIT");
                        }
                        if (data->deviceMemoryProperties.memoryTypes[j].propertyFlags & VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT) {
                            flags.append(" LAZILY_ALLOCATED_BIT");
                        }
                        if (data->deviceMemoryProperties.memoryTypes[j].propertyFlags & VK_MEMORY_PROPERTY_PROTECTED_BIT) {
                            flags.append(" PROTECTED_BIT");
                        }
                        if (data->deviceMemoryProperties.memoryTypes[j].propertyFlags & VK_MEMORY_PROPERTY_DEVICE_COHERENT_BIT_AMD) {
                            flags.append(" VK_MEMORY_PROPERTY_DEVICE_COHERENT_BIT_AMD");
                        }
                        if (data->deviceMemoryProperties.memoryTypes[j].propertyFlags & VK_MEMORY_PROPERTY_DEVICE_UNCACHED_BIT_AMD) {
                            flags.append(" VK_MEMORY_PROPERTY_DEVICE_UNCACHED_BIT_AMD");
                        }
                        RenderSystem::LOGGER->info("\tMemory flags %s", flags.c_str());
                    }
                }
                RenderSystem::LOGGER->info("");
            }
        }

        static void printDeviceQueueFamilies(DeviceData* data) {
            int counter = 0;
            RenderSystem::LOGGER->info("Queue families:");
            for (VkQueueFamilyProperties const family : data->queueFamilies) {
                std::string flags = "";
                RenderSystem::LOGGER->info("\tFamily #%i:", counter);
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
                counter++;
            }
        }

        static void printDeviceData(DeviceData* data, bool printProperties, bool printLimits, bool printFeatures, bool printMemoryProperties, bool printQueueFamilies) {
            RenderSystem::LOGGER->info("##### Device Data #####");
            if (printProperties)
                printDeviceProperties(data);
            if (printLimits)
                printDeviceLimits(data);
            if (printFeatures)
                printSupportedDeviceFeatures(data);
            if (printMemoryProperties)
                printDeviceMemoryProperties(data);
            if (printQueueFamilies)
                printDeviceQueueFamilies(data);
            RenderSystem::LOGGER->info("#######################");
        }

        static void printSurfaceData(SurfaceData* data) {
            RenderSystem::LOGGER->info("##### Surface Data #####");
            RenderSystem::LOGGER->info("\tMin extent: [%ul/%lu]", data->surfaceCapabilities.minImageExtent.width, data->surfaceCapabilities.minImageExtent.height);
            RenderSystem::LOGGER->info("\tMax extent: [%ul/%lu]", data->surfaceCapabilities.maxImageExtent.width, data->surfaceCapabilities.maxImageExtent.height);
            RenderSystem::LOGGER->info("\tFormats:");
            for (VkSurfaceFormatKHR format : data->surfaceFormats) {
                switch (format.format) {
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
                    RenderSystem::LOGGER->info("\t%i %i", format.format, format.colorSpace);
                    break;
                }

            }
            RenderSystem::LOGGER->info("\tPresent modes:");
            for (VkPresentModeKHR mode : data->presentModes) {
                switch (mode) {
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
            }
            RenderSystem::LOGGER->info("#######################");
        }
    };

}//end namespace