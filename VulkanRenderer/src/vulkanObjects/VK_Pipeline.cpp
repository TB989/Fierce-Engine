#include "VK_Pipeline.h"

#include "glm.hpp"

#include "src/vulkanObjects/VK_Device.h"

#include "src/renderSystem/RenderSystem.h"

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

        m_pipelineLayoutInfo={};
        m_pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        m_pipelineLayoutInfo.pNext = nullptr;
        m_pipelineLayoutInfo.flags = 0;

        m_createInfo = {};
        m_createInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        m_createInfo.pNext = nullptr;
        m_createInfo.flags = 0;
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
	}

	void VK_Pipeline::create(){
        //Vertex input
        m_inputBindingDescription = {};
        m_inputBindingDescription.binding = 0;
        m_inputBindingDescription.stride = m_vertexSize * sizeof(float);
        m_inputBindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

        m_vertexInputInfo = {};
        m_vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
        m_vertexInputInfo.pNext = nullptr;
        m_vertexInputInfo.flags = 0;
        m_vertexInputInfo.vertexBindingDescriptionCount = 1;
        m_vertexInputInfo.pVertexBindingDescriptions = &m_inputBindingDescription;
        m_vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(m_attributeDescriptions.size());
        m_vertexInputInfo.pVertexAttributeDescriptions = m_attributeDescriptions.data();

        m_createInfo.pVertexInputState = &m_vertexInputInfo;

        //Pipeline layout
        m_pipelineLayoutInfo.setLayoutCount = static_cast<uint32_t>(m_descriptorSetLayouts.size());
        m_pipelineLayoutInfo.pSetLayouts = m_descriptorSetLayouts.data();
        m_pipelineLayoutInfo.pushConstantRangeCount = static_cast<uint32_t>(m_pushConstantRanges.size());
        m_pipelineLayoutInfo.pPushConstantRanges = m_pushConstantRanges.data();

        if (vkCreatePipelineLayout(m_device->getDevice(), &m_pipelineLayoutInfo, nullptr, &m_pipelineLayout) != VK_SUCCESS) {
            RenderSystem::LOGGER->error("Failed to create pipeline layout.");
        }
        m_createInfo.layout = m_pipelineLayout;
        m_device->debug_setName(VK_OBJECT_TYPE_PIPELINE_LAYOUT, (uint64_t)m_pipelineLayout, "Pipeline layout 2D");

        //Shaders
        VkPipelineShaderStageCreateInfo shaderStages[] = { m_vertexShaderStageInfo ,m_fragmentShaderStageInfo };
        m_createInfo.stageCount = 2;
        m_createInfo.pStages = shaderStages;

        //Create pipeline
        if (vkCreateGraphicsPipelines(m_device->getDevice(), VK_NULL_HANDLE, 1, &m_createInfo, nullptr, &m_graphicsPipeline) != VK_SUCCESS) {
            RenderSystem::LOGGER->error("Failed to create pipeline.");
        }
        m_device->debug_setName(VK_OBJECT_TYPE_PIPELINE, (uint64_t)m_graphicsPipeline, "Pipeline 2D");
	}

    void VK_Pipeline::addVertexShader(VkShaderModule shader){
        m_vertexShaderStageInfo.module = shader;
    }

    void VK_Pipeline::addFragmentShader(VkShaderModule shader){
        m_fragmentShaderStageInfo.module = shader;
    }

    void VK_Pipeline::addVertexInput(uint32_t location,VkFormat format){
        VkVertexInputAttributeDescription description= {};
        description.binding = 0;
        description.location = location;
        description.format = format;
        description.offset = m_vertexSize* sizeof(float);
        m_attributeDescriptions.push_back(description);
        switch (format) {
        case VK_FORMAT_R32G32_SFLOAT:
            m_vertexSize += 2;
            break;
        case VK_FORMAT_R32G32B32_SFLOAT:
            m_vertexSize += 3;
            break;
        }
    }

    void VK_Pipeline::addDescriptorSetLayout(VkDescriptorSetLayout descriptorSetLayout){
        m_descriptorSetLayouts.push_back(descriptorSetLayout);
    }

    void VK_Pipeline::addPushConstantRange(VkShaderStageFlags shaderStages,uint32_t size,uint32_t offset) {
        VkPushConstantRange range = {};
        range.stageFlags = shaderStages;
        range.size = size;
        range.offset = offset;
        m_pushConstantRanges.push_back(range);
    }

}//end namespace