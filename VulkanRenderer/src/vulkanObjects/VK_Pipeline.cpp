#include "VK_Pipeline.h"

#include "glm.hpp"

#include "vulkanObjects/VK_Device.h"

#include "renderSystem/RenderSystem.h"

namespace Fierce {

	VK_Pipeline::VK_Pipeline(VK_Device* device, VkRenderPass renderpass){
		m_device = device;
        m_renderpass = renderpass;

        m_vertexShaderStageInfo = {};
        m_vertexShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        m_vertexShaderStageInfo.pNext = nullptr;
        m_vertexShaderStageInfo.flags = 0;
        m_vertexShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
        m_vertexShaderStageInfo.pName = "main";
        m_vertexShaderStageInfo.pSpecializationInfo = nullptr;

        m_fragmentShaderStageInfo = {};
        m_fragmentShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        m_fragmentShaderStageInfo.pNext = nullptr;
        m_fragmentShaderStageInfo.flags = 0;
        m_fragmentShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
        m_fragmentShaderStageInfo.pName = "main";
        m_fragmentShaderStageInfo.pSpecializationInfo = nullptr;

        //Mesh/////////////////////////////////////////////////////////////////////////////
        m_inputBindingDescription = {};
        m_inputBindingDescription.binding = 0;
        m_inputBindingDescription.stride = 7*sizeof(float);
        m_inputBindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

        VkVertexInputAttributeDescription descriptionPosition = {};
        descriptionPosition.binding = 0;
        descriptionPosition.location = 0;
        descriptionPosition.format = VK_FORMAT_R32G32_SFLOAT;
        descriptionPosition.offset = 0;
        m_attributeDescriptions.push_back(descriptionPosition);

        VkVertexInputAttributeDescription descriptionColor = {};
        descriptionColor.binding = 0;
        descriptionColor.location = 1;
        descriptionColor.format = VK_FORMAT_R32G32B32_SFLOAT;
        descriptionColor.offset = 2*sizeof(float);
        m_attributeDescriptions.push_back(descriptionColor);

        VkVertexInputAttributeDescription descriptionTex = {};
        descriptionTex.binding = 0;
        descriptionTex.location = 2;
        descriptionTex.format = VK_FORMAT_R32G32_SFLOAT;
        descriptionTex.offset = 5 * sizeof(float);
        m_attributeDescriptions.push_back(descriptionTex);

        ////////////////////////////////////////////////////////////////////////////////////

        m_vertexInputInfo = {};
        m_vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
        m_vertexInputInfo.pNext = nullptr;
        m_vertexInputInfo.flags = 0;
        m_vertexInputInfo.vertexBindingDescriptionCount = 1;
        m_vertexInputInfo.pVertexBindingDescriptions = &m_inputBindingDescription;
        m_vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(m_attributeDescriptions.size());
        m_vertexInputInfo.pVertexAttributeDescriptions = m_attributeDescriptions.data();

        m_inputAssembly = {};
        m_inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
        m_inputAssembly.pNext = nullptr;
        m_inputAssembly.flags = 0;
        m_inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
        m_inputAssembly.primitiveRestartEnable = VK_FALSE;

        m_viewport = {};
        m_viewport.x = 0.0f;
        m_viewport.y = 0.0f;
        m_viewport.width = (float)m_device->getSurfaceData()->swapchainWidth;
        m_viewport.height = (float)m_device->getSurfaceData()->swapchainHeight;
        m_viewport.minDepth = 0.0f;
        m_viewport.maxDepth = 1.0f;

        m_scissor = {};
        m_scissor.offset = { 0, 0 };
        m_scissor.extent = { device->getSurfaceData()->swapchainWidth, device->getSurfaceData()->swapchainHeight };

        m_viewportState = {};
        m_viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        m_viewportState.pNext = nullptr;
        m_viewportState.flags = 0;
        m_viewportState.viewportCount = 1;
        //m_viewportState.pViewports = &m_viewport;
        m_viewportState.scissorCount = 1;
        //m_viewportState.pScissors = &m_scissor;

        m_rasterizer = {};
        m_rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
        m_rasterizer.pNext = nullptr;
        m_rasterizer.flags = 0;
        m_rasterizer.depthClampEnable = VK_FALSE;
        m_rasterizer.rasterizerDiscardEnable = VK_FALSE;
        m_rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
        m_rasterizer.cullMode = VK_CULL_MODE_NONE;
        m_rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
        m_rasterizer.depthBiasEnable = VK_FALSE;
        m_rasterizer.depthBiasConstantFactor = 0.0f;
        m_rasterizer.depthBiasClamp = 0.0f;
        m_rasterizer.depthBiasSlopeFactor = 0.0f;
        m_rasterizer.lineWidth = 1.0f;

        m_multisampling = {};
        m_multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        m_multisampling.pNext = nullptr;
        m_multisampling.flags = 0;
        m_multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
        m_multisampling.sampleShadingEnable = VK_FALSE;
        m_multisampling.minSampleShading = 1.0f;
        m_multisampling.pSampleMask = nullptr;
        m_multisampling.alphaToCoverageEnable = VK_FALSE;
        m_multisampling.alphaToOneEnable = VK_FALSE;

        m_colorBlendAttachment = {};
        m_colorBlendAttachment.blendEnable = VK_FALSE;
        m_colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
        m_colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
        m_colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
        m_colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
        m_colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
        m_colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;
        m_colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;

        m_colorBlending = {};
        m_colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
        m_colorBlending.pNext = nullptr;
        m_colorBlending.flags = 0;
        m_colorBlending.logicOpEnable = VK_FALSE;
        m_colorBlending.logicOp = VK_LOGIC_OP_COPY;
        m_colorBlending.attachmentCount = 1;
        m_colorBlending.pAttachments = &m_colorBlendAttachment;
        m_colorBlending.blendConstants[0] = 0.0f;
        m_colorBlending.blendConstants[1] = 0.0f;
        m_colorBlending.blendConstants[2] = 0.0f;
        m_colorBlending.blendConstants[3] = 0.0f;

        m_dynamicStates.push_back(VK_DYNAMIC_STATE_VIEWPORT);
        m_dynamicStates.push_back(VK_DYNAMIC_STATE_SCISSOR);
        m_dynamicState = {};
        m_dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
        m_dynamicState.pNext = nullptr;
        m_dynamicState.flags = 0;
        m_dynamicState.dynamicStateCount = static_cast<uint32_t>(m_dynamicStates.size());
        m_dynamicState.pDynamicStates = m_dynamicStates.data();

        //############################ Descriptors #####################################################################
        m_uboViewProjectionLayoutBinding = {};
        m_uboViewProjectionLayoutBinding.binding = 0;
        m_uboViewProjectionLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        m_uboViewProjectionLayoutBinding.descriptorCount = 1;
        m_uboViewProjectionLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
        m_uboViewProjectionLayoutBinding.pImmutableSamplers = nullptr;
        m_layoutBindings.push_back(m_uboViewProjectionLayoutBinding);

        m_uboModelLayoutBinding = {};
        m_uboModelLayoutBinding.binding = 0;
        m_uboModelLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        m_uboModelLayoutBinding.descriptorCount = 1;
        m_uboModelLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
        m_uboModelLayoutBinding.pImmutableSamplers = nullptr;
        m_layoutBindings.push_back(m_uboModelLayoutBinding);

        m_samplerLayoutBinding = {};
        m_samplerLayoutBinding.binding = 0;
        m_samplerLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        m_samplerLayoutBinding.descriptorCount = 1;
        m_samplerLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
        m_samplerLayoutBinding.pImmutableSamplers = nullptr;
        m_layoutBindings.push_back(m_samplerLayoutBinding);

        m_descriptorSetViewProjectionLayoutCreateInfo = {};
        m_descriptorSetViewProjectionLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        m_descriptorSetViewProjectionLayoutCreateInfo.pNext = nullptr;
        m_descriptorSetViewProjectionLayoutCreateInfo.flags = 0;
        m_descriptorSetViewProjectionLayoutCreateInfo.bindingCount = 1;
        m_descriptorSetViewProjectionLayoutCreateInfo.pBindings = &m_uboViewProjectionLayoutBinding;

        m_descriptorSetModelLayoutCreateInfo = {};
        m_descriptorSetModelLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        m_descriptorSetModelLayoutCreateInfo.pNext = nullptr;
        m_descriptorSetModelLayoutCreateInfo.flags = 0;
        m_descriptorSetModelLayoutCreateInfo.bindingCount = 1;
        m_descriptorSetModelLayoutCreateInfo.pBindings = &m_uboModelLayoutBinding;

        m_descriptorSetSamplerLayoutCreateInfo = {};
        m_descriptorSetSamplerLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        m_descriptorSetSamplerLayoutCreateInfo.pNext = nullptr;
        m_descriptorSetSamplerLayoutCreateInfo.flags = 0;
        m_descriptorSetSamplerLayoutCreateInfo.bindingCount = 1;
        m_descriptorSetSamplerLayoutCreateInfo.pBindings = &m_samplerLayoutBinding;
        //###############################################################################################################

        m_pipelineLayoutInfo={};
        m_pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        m_pipelineLayoutInfo.pNext = nullptr;
        m_pipelineLayoutInfo.flags = 0;
        m_pipelineLayoutInfo.pushConstantRangeCount = 0;
        m_pipelineLayoutInfo.pPushConstantRanges = nullptr;

        m_createInfo = {};
        m_createInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        m_createInfo.pNext = nullptr;
        m_createInfo.flags = 0;
        m_createInfo.pVertexInputState = &m_vertexInputInfo;
        m_createInfo.pInputAssemblyState = &m_inputAssembly;
        m_createInfo.pTessellationState = nullptr;
        m_createInfo.pViewportState = &m_viewportState;
        m_createInfo.pRasterizationState = &m_rasterizer;
        m_createInfo.pMultisampleState = &m_multisampling;
        m_createInfo.pDepthStencilState = nullptr;
        m_createInfo.pColorBlendState = &m_colorBlending;
        m_createInfo.pDynamicState = &m_dynamicState;
        m_createInfo.renderPass = m_renderpass;
        m_createInfo.subpass = 0;
        m_createInfo.basePipelineHandle = VK_NULL_HANDLE;
        m_createInfo.basePipelineIndex = -1;
	}

	VK_Pipeline::~VK_Pipeline(){
        vkDestroyPipeline(m_device->getDevice(), m_graphicsPipeline, nullptr);
        vkDestroyPipelineLayout(m_device->getDevice(), m_pipelineLayout, nullptr);
        vkDestroyDescriptorSetLayout(m_device->getDevice(),m_descriptorSetLayoutViewProjection,nullptr);
        vkDestroyDescriptorSetLayout(m_device->getDevice(), m_descriptorSetLayoutModel, nullptr);
        vkDestroyDescriptorSetLayout(m_device->getDevice(), m_descriptorSetLayoutSampler, nullptr);
	}

	void VK_Pipeline::create(){
        if (vkCreateDescriptorSetLayout(m_device->getDevice(), &m_descriptorSetViewProjectionLayoutCreateInfo, nullptr, &m_descriptorSetLayoutViewProjection) != VK_SUCCESS) {
            RenderSystem::LOGGER->error("Failed to create descriptor set layout.");
        }
        if (vkCreateDescriptorSetLayout(m_device->getDevice(), &m_descriptorSetModelLayoutCreateInfo, nullptr, &m_descriptorSetLayoutModel) != VK_SUCCESS) {
            RenderSystem::LOGGER->error("Failed to create descriptor set layout.");
        }
        if (vkCreateDescriptorSetLayout(m_device->getDevice(), &m_descriptorSetSamplerLayoutCreateInfo, nullptr, &m_descriptorSetLayoutSampler) != VK_SUCCESS) {
            RenderSystem::LOGGER->error("Failed to create descriptor set layout.");
        }
        m_descriptorLayouts.push_back(m_descriptorSetLayoutViewProjection);
        m_descriptorLayouts.push_back(m_descriptorSetLayoutModel);
        m_descriptorLayouts.push_back(m_descriptorSetLayoutSampler);

        m_pipelineLayoutInfo.setLayoutCount = static_cast<uint32_t>(m_descriptorLayouts.size());
        m_pipelineLayoutInfo.pSetLayouts = m_descriptorLayouts.data();

        if (vkCreatePipelineLayout(m_device->getDevice(), &m_pipelineLayoutInfo, nullptr, &m_pipelineLayout) != VK_SUCCESS) {
            RenderSystem::LOGGER->error("Failed to create pipeline layout.");
        }
        m_createInfo.layout = m_pipelineLayout;

        VkPipelineShaderStageCreateInfo shaderStages[] = { m_vertexShaderStageInfo ,m_fragmentShaderStageInfo };
        m_createInfo.stageCount = 2;
        m_createInfo.pStages = shaderStages;
        if (vkCreateGraphicsPipelines(m_device->getDevice(), VK_NULL_HANDLE, 1, &m_createInfo, nullptr, &m_graphicsPipeline) != VK_SUCCESS) {
            RenderSystem::LOGGER->error("Failed to create pipeline.");
        }
	}

    void VK_Pipeline::addVertexShader(VkShaderModule shader){
        m_vertexShaderStageInfo.module = shader;
    }

    void VK_Pipeline::addFragmentShader(VkShaderModule shader){
        m_fragmentShaderStageInfo.module = shader;
    }

}//end namespace