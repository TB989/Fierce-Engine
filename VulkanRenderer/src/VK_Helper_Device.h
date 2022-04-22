#pragma once

#include "Common.h"

#include "VK_Device.h"

class VK_Helper_Device{
public:
	static void getAllPhysicalDevices(VkInstance instance,std::vector<VkPhysicalDevice>* devices) {
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
        if (deviceCount == 0) {
            CHECK_VK(VK_ERROR_INCOMPATIBLE_DRIVER, "No graphics card with vulkan support found.");
        }
        devices->resize(deviceCount);
        vkEnumeratePhysicalDevices(instance, &deviceCount, devices->data());
	}

    static void getDeviceData(VkPhysicalDevice device, VkSurfaceKHR surface, DeviceData* data) {
        vkGetPhysicalDeviceProperties(device, &data->deviceProperties);
        vkGetPhysicalDeviceFeatures(device, &data->deviceFeatures);
        vkGetPhysicalDeviceMemoryProperties(device, &data->deviceMemoryProperties);
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
        data->queueFamilies.resize(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, data->queueFamilies.data());

        data->presentSupport.clear();
        data->presentSupport.resize(queueFamilyCount);
        for (int i = 0;i< queueFamilyCount;i++) {
            VkBool32 supported;
            vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &supported);

            if (supported) {
                data->presentSupport[i] = true;
            }
        }
    }

    static void getSurfaceData(VkPhysicalDevice device, VkSurfaceKHR surface, SurfaceData* data) {
        CHECK_VK(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &data->surfaceCapabilities), "Failed to get surface capabilities.");
        uint32_t formatCount;
        CHECK_VK(vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr), "Failed to get surface formats.");
        data->surfaceFormats.resize(formatCount);
        CHECK_VK(vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, data->surfaceFormats.data()), "Failed to get surface formats.");
        uint32_t presentModeCount;
        CHECK_VK(vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr), "Failed to get present modes.");
        data->presentModes.resize(presentModeCount);
        CHECK_VK(vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, data->presentModes.data()), "Failed to get present modes.");
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
        LOGGER->info("Device: %s (%s)", data->deviceProperties.deviceName, deviceType.c_str());
    }

    static void getSampleCounts(VkSampleCountFlags flags,std::string *samples) {
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
        LOGGER->info("Limits:");
        LOGGER->info("\tBufferImageGranularity: %llu", data->deviceProperties.limits.bufferImageGranularity);
        LOGGER->info("\tDiscreteQueuePriorities: %lu", data->deviceProperties.limits.discreteQueuePriorities);
        getSampleCounts(data->deviceProperties.limits.framebufferColorSampleCounts,&flags);
        LOGGER->info("\tFramebufferColorSampleCounts: %s", flags.c_str());
        getSampleCounts(data->deviceProperties.limits.framebufferDepthSampleCounts, &flags);
        LOGGER->info("\tFramebufferDepthSampleCounts: %s", flags.c_str());
        getSampleCounts(data->deviceProperties.limits.framebufferNoAttachmentsSampleCounts, &flags);
        LOGGER->info("\tFramebufferNoAttachmentsSampleCounts: %s", flags.c_str());
        getSampleCounts(data->deviceProperties.limits.framebufferStencilSampleCounts, &flags);
        LOGGER->info("\tFramebufferStencilSampleCounts: %s", flags.c_str());
        LOGGER->info("\tLineWidthGranularity: %1.3f", data->deviceProperties.limits.lineWidthGranularity);
        LOGGER->info("\tLineWidthRange: %1.3f", data->deviceProperties.limits.lineWidthRange);
        LOGGER->info("\tMaxBoundDescriptorSets: %lu", data->deviceProperties.limits.maxBoundDescriptorSets);
        LOGGER->info("\tMaxClipDistances: %lu", data->deviceProperties.limits.maxClipDistances);
        LOGGER->info("\tMaxColorAttachments: %lu", data->deviceProperties.limits.maxColorAttachments);
        LOGGER->info("\tMaxCombinedClipAndCullDistances: %lu", data->deviceProperties.limits.maxCombinedClipAndCullDistances);
        LOGGER->info("\tMaxComputeSharedMemorySize: %lu", data->deviceProperties.limits.maxComputeSharedMemorySize);
        LOGGER->info("\tMaxComputeWorkGroupCount: %lu", data->deviceProperties.limits.maxComputeWorkGroupCount);
        LOGGER->info("\tMaxComputeWorkGroupInvocations: %lu", data->deviceProperties.limits.maxComputeWorkGroupInvocations);
        LOGGER->info("\tMaxComputeWorkGroupSize: %lu", data->deviceProperties.limits.maxComputeWorkGroupSize);
        LOGGER->info("\tMaxCullDistances: %lu", data->deviceProperties.limits.maxCullDistances);
        LOGGER->info("\tMaxDescriptorSetInputAttachments: %lu", data->deviceProperties.limits.maxDescriptorSetInputAttachments);
        LOGGER->info("\tMaxDescriptorSetSampledImages: %lu", data->deviceProperties.limits.maxDescriptorSetSampledImages);
        LOGGER->info("\tMaxDescriptorSetSamplers: %lu", data->deviceProperties.limits.maxDescriptorSetSamplers);
        LOGGER->info("\tMaxDescriptorSetStorageBuffers: %lu", data->deviceProperties.limits.maxDescriptorSetStorageBuffers);
        LOGGER->info("\tMaxDescriptorSetStorageBuffersDynamic: %lu", data->deviceProperties.limits.maxDescriptorSetStorageBuffersDynamic);
        LOGGER->info("\tMaxDescriptorSetStorageImages: %lu", data->deviceProperties.limits.maxDescriptorSetStorageImages);
        LOGGER->info("\tMaxDescriptorSetUniformBuffers: %lu", data->deviceProperties.limits.maxDescriptorSetUniformBuffers);
        LOGGER->info("\tMaxDescriptorSetUniformBuffersDynamic: %lu", data->deviceProperties.limits.maxDescriptorSetUniformBuffersDynamic);
        LOGGER->info("\tMaxDrawIndexedIndexValue: %lu", data->deviceProperties.limits.maxDrawIndexedIndexValue);
        LOGGER->info("\tMaxDrawIndirectCount: %lu", data->deviceProperties.limits.maxDrawIndirectCount);
        LOGGER->info("\tMaxFragmentCombinedOutputResources: %lu", data->deviceProperties.limits.maxFragmentCombinedOutputResources);
        LOGGER->info("\tMaxFragmentDualSrcAttachments: %lu", data->deviceProperties.limits.maxFragmentDualSrcAttachments);
        LOGGER->info("\tMaxFragmentInputComponents: %lu", data->deviceProperties.limits.maxFragmentInputComponents);
        LOGGER->info("\tMaxFragmentOutputAttachments: %lu", data->deviceProperties.limits.maxFragmentOutputAttachments);
        LOGGER->info("\tMaxFramebufferHeight: %lu", data->deviceProperties.limits.maxFramebufferHeight);
        LOGGER->info("\tMaxFramebufferLayers: %lu", data->deviceProperties.limits.maxFramebufferLayers);
        LOGGER->info("\tMaxFramebufferWidth: %lu", data->deviceProperties.limits.maxFramebufferWidth);
        LOGGER->info("\tMaxGeometryInputComponents: %lu", data->deviceProperties.limits.maxGeometryInputComponents);
        LOGGER->info("\tMaxGeometryOutputComponents: %lu", data->deviceProperties.limits.maxGeometryOutputComponents);
        LOGGER->info("\tMaxGeometryOutputVertices: %lu", data->deviceProperties.limits.maxGeometryOutputVertices);
        LOGGER->info("\tMaxGeometryShaderInvocations: %lu", data->deviceProperties.limits.maxGeometryShaderInvocations);
        LOGGER->info("\tMaxGeometryTotalOutputComponents: %lu", data->deviceProperties.limits.maxGeometryTotalOutputComponents);
        LOGGER->info("\tMaxImageArrayLayers: %lu", data->deviceProperties.limits.maxImageArrayLayers);
        LOGGER->info("\tMaxImageDimension1D: %lu", data->deviceProperties.limits.maxImageDimension1D);
        LOGGER->info("\tMaxImageDimension2D: %lu", data->deviceProperties.limits.maxImageDimension2D);
        LOGGER->info("\tMaxImageDimension3D: %lu", data->deviceProperties.limits.maxImageDimension3D);
        LOGGER->info("\tMaxImageDimensionCube: %lu", data->deviceProperties.limits.maxImageDimensionCube);
        LOGGER->info("\tMaxInterpolationOffset: %1.3f", data->deviceProperties.limits.maxInterpolationOffset);
        LOGGER->info("\tMaxMemoryAllocationCount: %lu", data->deviceProperties.limits.maxMemoryAllocationCount);
        LOGGER->info("\tMaxPerStageDescriptorInputAttachments: %lu", data->deviceProperties.limits.maxPerStageDescriptorInputAttachments);
        LOGGER->info("\tMaxPerStageDescriptorSampledImages: %lu", data->deviceProperties.limits.maxPerStageDescriptorSampledImages);
        LOGGER->info("\tMaxPerStageDescriptorSamplers: %lu", data->deviceProperties.limits.maxPerStageDescriptorSamplers);
        LOGGER->info("\tMaxPerStageDescriptorStorageBuffers: %lu", data->deviceProperties.limits.maxPerStageDescriptorStorageBuffers);
        LOGGER->info("\tMaxPerStageDescriptorStorageImages: %lu", data->deviceProperties.limits.maxPerStageDescriptorStorageImages);
        LOGGER->info("\tMaxPerStageDescriptorUniformBuffers: %lu", data->deviceProperties.limits.maxPerStageDescriptorUniformBuffers);
        LOGGER->info("\tMaxPerStageResources: %lu", data->deviceProperties.limits.maxPerStageResources);
        LOGGER->info("\tMaxPushConstantsSize: %lu", data->deviceProperties.limits.maxPushConstantsSize);
        LOGGER->info("\tMaxSampleMaskWords: %lu", data->deviceProperties.limits.maxSampleMaskWords);
        LOGGER->info("\tMaxSamplerAllocationCount: %lu", data->deviceProperties.limits.maxSamplerAllocationCount);
        LOGGER->info("\tMaxSamplerAnisotropy: %1.3f", data->deviceProperties.limits.maxSamplerAnisotropy);
        LOGGER->info("\tMaxSamplerLodBias: %1.3f", data->deviceProperties.limits.maxSamplerLodBias);
        LOGGER->info("\tMaxStorageBufferRange: %lu", data->deviceProperties.limits.maxStorageBufferRange);
        LOGGER->info("\tMaxTessellationControlPerPatchOutputComponents: %lu", data->deviceProperties.limits.maxTessellationControlPerPatchOutputComponents);
        LOGGER->info("\tMaxTessellationControlPerVertexInputComponents: %lu", data->deviceProperties.limits.maxTessellationControlPerVertexInputComponents);
        LOGGER->info("\tMaxTessellationControlPerVertexOutputComponents: %lu", data->deviceProperties.limits.maxTessellationControlPerVertexOutputComponents);
        LOGGER->info("\tMaxTessellationControlTotalOutputComponents: %lu", data->deviceProperties.limits.maxTessellationControlTotalOutputComponents);
        LOGGER->info("\tMaxTessellationEvaluationInputComponents: %lu", data->deviceProperties.limits.maxTessellationEvaluationInputComponents);
        LOGGER->info("\tMaxTessellationEvaluationOutputComponents: %lu", data->deviceProperties.limits.maxTessellationEvaluationOutputComponents);
        LOGGER->info("\tMaxTessellationGenerationLevel: %lu", data->deviceProperties.limits.maxTessellationGenerationLevel);
        LOGGER->info("\tMaxTessellationPatchSize: %lu", data->deviceProperties.limits.maxTessellationPatchSize);
        LOGGER->info("\tMaxTexelBufferElements: %lu", data->deviceProperties.limits.maxTexelBufferElements);
        LOGGER->info("\tMaxTexelGatherOffset: %lu", data->deviceProperties.limits.maxTexelGatherOffset);
        LOGGER->info("\tMaxTexelOffset: %lu", data->deviceProperties.limits.maxTexelOffset);
        LOGGER->info("\tMaxUniformBufferRange: %lu", data->deviceProperties.limits.maxUniformBufferRange);
        LOGGER->info("\tMaxVertexInputAttributeOffset: %lu", data->deviceProperties.limits.maxVertexInputAttributeOffset);
        LOGGER->info("\tMaxVertexInputAttributes: %lu", data->deviceProperties.limits.maxVertexInputAttributes);
        LOGGER->info("\tMaxVertexInputBindings: %lu", data->deviceProperties.limits.maxVertexInputBindings);
        LOGGER->info("\tMaxVertexInputBindingStride: %lu", data->deviceProperties.limits.maxVertexInputBindingStride);
        LOGGER->info("\tMaxVertexOutputComponents: %lu", data->deviceProperties.limits.maxVertexOutputComponents);
        LOGGER->info("\tMaxViewportDimensions: %lu", data->deviceProperties.limits.maxViewportDimensions);
        LOGGER->info("\tMaxViewports: %lu", data->deviceProperties.limits.maxViewports);
        LOGGER->info("\tMinInterpolationOffset: %1.3f", data->deviceProperties.limits.minInterpolationOffset);
        LOGGER->info("\tMinMemoryMapAlignment: %lu", data->deviceProperties.limits.minMemoryMapAlignment);
        LOGGER->info("\tMinStorageBufferOffsetAlignment: %lu", data->deviceProperties.limits.minStorageBufferOffsetAlignment);
        LOGGER->info("\tMipmapPrecisionBits: %lu", data->deviceProperties.limits.mipmapPrecisionBits);
        LOGGER->info("\tNonCoherentAtomSize: %lu", data->deviceProperties.limits.nonCoherentAtomSize);
        LOGGER->info("\tOptimalBufferCopyOffsetAlignment: %lu", data->deviceProperties.limits.optimalBufferCopyOffsetAlignment);
        LOGGER->info("\tOptimalBufferCopyRowPitchAlignment: %lu", data->deviceProperties.limits.optimalBufferCopyRowPitchAlignment);
        LOGGER->info("\tPointSizeGranularity: %1.3f", data->deviceProperties.limits.pointSizeGranularity);
        LOGGER->info("\tPointSizeRange: %1.3f", data->deviceProperties.limits.pointSizeRange);
        getSampleCounts(data->deviceProperties.limits.sampledImageColorSampleCounts, &flags);
        LOGGER->info("\tSampledImageColorSampleCounts: %s", flags.c_str());
        getSampleCounts(data->deviceProperties.limits.sampledImageDepthSampleCounts, &flags);
        LOGGER->info("\tSampledImageDepthSampleCounts: %s", flags.c_str());
        getSampleCounts(data->deviceProperties.limits.sampledImageIntegerSampleCounts, &flags);
        LOGGER->info("\tSampledImageIntegerSampleCounts: %s", flags.c_str());
        getSampleCounts(data->deviceProperties.limits.sampledImageStencilSampleCounts, &flags);
        LOGGER->info("\tSampledImageStencilSampleCounts: %s", flags.c_str());
        LOGGER->info("\tSparseAddressSpaceSize: %lu", data->deviceProperties.limits.sparseAddressSpaceSize);
        LOGGER->info("\tStandardSampleLocations: %s", data->deviceProperties.limits.standardSampleLocations ? "true" : "false");
        getSampleCounts(data->deviceProperties.limits.storageImageSampleCounts, &flags);
        LOGGER->info("\tStorageImageSampleCounts: %s", flags.c_str());
        LOGGER->info("\tStrictLines: %s", data->deviceProperties.limits.strictLines ? "true" : "false");
        LOGGER->info("\tSubPixelInterpolationOffsetBits: %lu", data->deviceProperties.limits.subPixelInterpolationOffsetBits);
        LOGGER->info("\tSubPixelPrecisionBits: %lu", data->deviceProperties.limits.subPixelPrecisionBits);
        LOGGER->info("\tSubTexelPrecisionBits: %lu", data->deviceProperties.limits.subTexelPrecisionBits);
        LOGGER->info("\tTimestampComputeAndGraphics: %s", data->deviceProperties.limits.timestampComputeAndGraphics ? "true" : "false");
        LOGGER->info("\tTimestampPeriod: %1.3f", data->deviceProperties.limits.timestampPeriod);
        LOGGER->info("\tViewportBoundsRange: %1.3f", data->deviceProperties.limits.viewportBoundsRange);
        LOGGER->info("\tViewportSubPixelBits: %lu", data->deviceProperties.limits.viewportSubPixelBits);
    }

    static void printDeviceFeatures(DeviceData* data) {
        LOGGER->info("Features:");
        LOGGER->info("\tAlpahToOne: %s", data->deviceFeatures.alphaToOne?"true":"false");
        LOGGER->info("\tDepthBiasClamp: %s", data->deviceFeatures.depthBiasClamp ? "true" : "false");
        LOGGER->info("\tDepthBounds: %s", data->deviceFeatures.depthBounds ? "true" : "false");
        LOGGER->info("\tDepthClamp: %s", data->deviceFeatures.depthClamp ? "true" : "false");
        LOGGER->info("\tDrawIndirectFirstInstance: %s", data->deviceFeatures.drawIndirectFirstInstance ? "true" : "false");
        LOGGER->info("\tDualSrcBlend: %s", data->deviceFeatures.dualSrcBlend ? "true" : "false");
        LOGGER->info("\tFillModeNonSolid: %s", data->deviceFeatures.fillModeNonSolid ? "true" : "false");
        LOGGER->info("\tFragmentStoresAndAtomics: %s", data->deviceFeatures.fragmentStoresAndAtomics ? "true" : "false");
        LOGGER->info("\tFullDrawIndexUint32: %s", data->deviceFeatures.fullDrawIndexUint32 ? "true" : "false");
        LOGGER->info("\tGeometryShader: %s", data->deviceFeatures.geometryShader ? "true" : "false");
        LOGGER->info("\tImageCubeArray: %s", data->deviceFeatures.imageCubeArray ? "true" : "false");
        LOGGER->info("\tIndependentBlend: %s", data->deviceFeatures.independentBlend ? "true" : "false");
        LOGGER->info("\tInheritedQueries: %s", data->deviceFeatures.inheritedQueries ? "true" : "false");
        LOGGER->info("\tLargePoints: %s", data->deviceFeatures.largePoints ? "true" : "false");
        LOGGER->info("\tLogicOp: %s", data->deviceFeatures.logicOp ? "true" : "false");
        LOGGER->info("\tMultiDrawIndirect: %s", data->deviceFeatures.multiDrawIndirect ? "true" : "false");
        LOGGER->info("\tMultiViewport: %s", data->deviceFeatures.multiViewport ? "true" : "false");
        LOGGER->info("\tOcclusionQueryPrecise: %s", data->deviceFeatures.occlusionQueryPrecise ? "true" : "false");
        LOGGER->info("\tPipelineStatisticsQuery: %s", data->deviceFeatures.pipelineStatisticsQuery ? "true" : "false");
        LOGGER->info("\tRobustBufferAccess: %s", data->deviceFeatures.robustBufferAccess ? "true" : "false");
        LOGGER->info("\tSamplerAnisotropy: %s", data->deviceFeatures.samplerAnisotropy ? "true" : "false");
        LOGGER->info("\tSampleRateShading: %s", data->deviceFeatures.sampleRateShading ? "true" : "false");
        LOGGER->info("\tShaderClipDistance: %s", data->deviceFeatures.shaderClipDistance ? "true" : "false");
        LOGGER->info("\tShaderCullDistance: %s", data->deviceFeatures.shaderCullDistance ? "true" : "false");
        LOGGER->info("\tShaderFloat64: %s", data->deviceFeatures.shaderFloat64 ? "true" : "false");
        LOGGER->info("\tShaderImageGatherExtended: %s", data->deviceFeatures.shaderImageGatherExtended ? "true" : "false");
        LOGGER->info("\tShaderInt16: %s", data->deviceFeatures.shaderInt16 ? "true" : "false");
        LOGGER->info("\tShaderInt64: %s", data->deviceFeatures.shaderInt64 ? "true" : "false");
        LOGGER->info("\tShaderResourceMinLod: %s", data->deviceFeatures.shaderResourceMinLod ? "true" : "false");
        LOGGER->info("\tShaderResourceResidency: %s", data->deviceFeatures.shaderResourceResidency ? "true" : "false");
        LOGGER->info("\tShaderSampledImageArrayDynamicIndexing: %s", data->deviceFeatures.shaderSampledImageArrayDynamicIndexing ? "true" : "false");
        LOGGER->info("\tShaderStorageBufferArrayDynamicIndexing: %s", data->deviceFeatures.shaderStorageBufferArrayDynamicIndexing ? "true" : "false");
        LOGGER->info("\tShaderStorageImageArrayDynamicIndexing: %s", data->deviceFeatures.shaderStorageImageArrayDynamicIndexing ? "true" : "false");
        LOGGER->info("\tShaderStorageImageExtendedFormats: %s", data->deviceFeatures.shaderStorageImageExtendedFormats ? "true" : "false");
        LOGGER->info("\tShaderStorageImageMultisample: %s", data->deviceFeatures.shaderStorageImageMultisample ? "true" : "false");
        LOGGER->info("\tShaderStorageImageReadWithoutFormat: %s", data->deviceFeatures.shaderStorageImageReadWithoutFormat ? "true" : "false");
        LOGGER->info("\tShaderStorageImageWriteWithoutFormat: %s", data->deviceFeatures.shaderStorageImageWriteWithoutFormat ? "true" : "false");
        LOGGER->info("\tShaderTessellationAndGeometryPointSize: %s", data->deviceFeatures.shaderTessellationAndGeometryPointSize ? "true" : "false");
        LOGGER->info("\tShaderUniformBufferArrayDynamicIndexing: %s", data->deviceFeatures.shaderUniformBufferArrayDynamicIndexing ? "true" : "false");
        LOGGER->info("\tSparseBinding: %s", data->deviceFeatures.sparseBinding ? "true" : "false");
        LOGGER->info("\tSparseResidency2Samples: %s", data->deviceFeatures.sparseResidency2Samples ? "true" : "false");
        LOGGER->info("\tSparseResidency4Samples: %s", data->deviceFeatures.sparseResidency4Samples ? "true" : "false");
        LOGGER->info("\tSparseResidency8Samples: %s", data->deviceFeatures.sparseResidency8Samples ? "true" : "false");
        LOGGER->info("\tSparseResidency16Samples: %s", data->deviceFeatures.sparseResidency16Samples ? "true" : "false");
        LOGGER->info("\tSparseResidencyAliased: %s", data->deviceFeatures.sparseResidencyAliased ? "true" : "false");
        LOGGER->info("\tSparseResidencyBuffer: %s", data->deviceFeatures.sparseResidencyBuffer ? "true" : "false");
        LOGGER->info("\tSparseResidencyImage2D: %s", data->deviceFeatures.sparseResidencyImage2D ? "true" : "false");
        LOGGER->info("\tSparseResidencyImage3D: %s", data->deviceFeatures.sparseResidencyImage3D ? "true" : "false");
        LOGGER->info("\tTessellationShader: %s", data->deviceFeatures.tessellationShader ? "true" : "false");
        LOGGER->info("\tTextureCompressionASTC_LDR: %s", data->deviceFeatures.textureCompressionASTC_LDR ? "true" : "false");
        LOGGER->info("\tTextureCompressionBC: %s", data->deviceFeatures.textureCompressionBC ? "true" : "false");
        LOGGER->info("\tTextureCompressionETC2: %s", data->deviceFeatures.textureCompressionETC2 ? "true" : "false");
        LOGGER->info("\tVariableMultisampleRate: %s", data->deviceFeatures.variableMultisampleRate ? "true" : "false");
        LOGGER->info("\tVertexPipelineStoresAndAtomics: %s", data->deviceFeatures.vertexPipelineStoresAndAtomics ? "true" : "false");
        LOGGER->info("\tWideLines: %s", data->deviceFeatures.wideLines ? "true" : "false");
    }

    static void printDeviceMemoryProperties(DeviceData* data) {
        LOGGER->info("Memory properties:");
        for (int i = 0;i< data->deviceMemoryProperties.memoryHeapCount;i++) {
            LOGGER->info("\tHeap %i:",i);
            LOGGER->info("\tMemory size: %llu GB", data->deviceMemoryProperties.memoryHeaps[i].size/100000000);
            std::string flags = "";
            if (data->deviceMemoryProperties.memoryHeaps[i].flags & VK_MEMORY_HEAP_DEVICE_LOCAL_BIT) {
                flags.append(" DEVICE_LOCAL_BIT");
            }
            if (data->deviceMemoryProperties.memoryHeaps[i].flags & VK_MEMORY_HEAP_MULTI_INSTANCE_BIT) {
                flags.append(" MULTI_INSTANCE_BIT");
            }
            LOGGER->info("\tHeap flags: %s", flags.c_str());

            for (int j = 0; j < data->deviceMemoryProperties.memoryTypeCount; j++) {
                if (data->deviceMemoryProperties.memoryTypes[j].heapIndex==i) {
                    LOGGER->info("\tMemory type %i:", j);
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
                    LOGGER->info("\tMemory flags %s", flags.c_str());
                }
            }
            LOGGER->info("");
        }
    }

    static void printDeviceQueueFamilies(DeviceData* data) {
        int counter = 0;
        LOGGER->info("Queue families:");
        for (VkQueueFamilyProperties family:data->queueFamilies) {
            std::string flags = "";
            LOGGER->info("\tFamily #%i:",counter);
            LOGGER->info("\tQueueCount: %i", family.queueCount);
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
            LOGGER->info("\tQueueFlags: %s", flags.c_str());
            LOGGER->info("");
            counter++;
        }
    }

    static void printDeviceData(DeviceData* data,bool printProperties, bool printLimits, bool printFeatures, bool printMemoryProperties, bool printQueueFamilies) {
        LOGGER->info("##### Device Data #####");
        if(printProperties)
            printDeviceProperties(data);
        if(printLimits)
            printDeviceLimits(data);
        if(printFeatures)
            printDeviceFeatures(data);
        if(printMemoryProperties)
            printDeviceMemoryProperties(data);
        if (printQueueFamilies)
            printDeviceQueueFamilies(data);
        LOGGER->info("#######################");
    }

    static void printSurfaceData(SurfaceData* data) {
        LOGGER->info("##### Surface Data #####");
        LOGGER->info("\tMin extent: [%ul/%lu]", data->surfaceCapabilities.minImageExtent.width, data->surfaceCapabilities.minImageExtent.height);
        LOGGER->info("\tMax extent: [%ul/%lu]", data->surfaceCapabilities.maxImageExtent.width, data->surfaceCapabilities.maxImageExtent.height);
        LOGGER->info("\tFormats:");
        for (VkSurfaceFormatKHR format:data->surfaceFormats) {
            switch (format.format) {
            case VK_FORMAT_B8G8R8A8_UNORM:
                LOGGER->info("\tVK_FORMAT_B8G8R8A8_UNORM VK_COLOR_SPACE_SRGB_NONLINEAR_KHR");
                break;
            case VK_FORMAT_B8G8R8A8_SRGB:
                LOGGER->info("\tVK_FORMAT_B8G8R8A8_SRGB VK_COLOR_SPACE_SRGB_NONLINEAR_KHR");
                break;
            case VK_FORMAT_A2B10G10R10_UNORM_PACK32:
                LOGGER->info("\tVK_FORMAT_A2B10G10R10_UNORM_PACK32 VK_COLOR_SPACE_SRGB_NONLINEAR_KHR");
                break;
            default:
                LOGGER->info("\t%i %i",format.format, format.colorSpace);
                break;
            }
            
        }
        LOGGER->info("\tPresent modes:");
        for (VkPresentModeKHR mode : data->presentModes) {
            switch (mode) {
            case VK_PRESENT_MODE_IMMEDIATE_KHR:
                LOGGER->info("\tVK_PRESENT_MODE_IMMEDIATE_KHR");
                break;
            case VK_PRESENT_MODE_MAILBOX_KHR:
                LOGGER->info("\tVK_PRESENT_MODE_MAILBOX_KHR");
                break;
            case VK_PRESENT_MODE_FIFO_KHR:
                LOGGER->info("\tVK_PRESENT_MODE_FIFO_KHR");
                break;
            case VK_PRESENT_MODE_FIFO_RELAXED_KHR:
                LOGGER->info("\tVK_PRESENT_MODE_FIFO_RELAXED_KHR");
                break;
            }
        }
        LOGGER->info("#######################");
    }
};