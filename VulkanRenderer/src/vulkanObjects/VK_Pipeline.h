#pragma once

#include "vulkan/vulkan.h"

#include <vector>

namespace Fierce {

	class VK_Device;

	class VK_Pipeline {
	public:
		VK_Pipeline(VK_Device* device,VkRenderPass renderpass);
		~VK_Pipeline();

		void create();
		VkPipeline getId() { return m_graphicsPipeline; }
		VkPipelineLayout getLayout() { return m_pipelineLayout; }
		VkDescriptorSetLayout getDescriptorSetLayout() { return m_descriptorSetLayout; }

	public:
		void addVertexShader(VkShaderModule shader);
		void addFragmentShader(VkShaderModule shader);

	private:
		//Create info
		VkGraphicsPipelineCreateInfo m_createInfo={};
		VkPipelineLayoutCreateInfo m_pipelineLayoutInfo = {};
		VkDescriptorSetLayoutCreateInfo m_descriptorSetLayoutInfo={};

		VkPipelineShaderStageCreateInfo m_vertexShaderStageInfo={};
		VkPipelineShaderStageCreateInfo m_fragmentShaderStageInfo={};
		VkPipelineVertexInputStateCreateInfo m_vertexInputInfo={};
		VkPipelineInputAssemblyStateCreateInfo m_inputAssembly={};
		VkViewport m_viewport={};
		VkRect2D m_scissor={};
		VkPipelineViewportStateCreateInfo m_viewportState={};
		VkPipelineRasterizationStateCreateInfo m_rasterizer={};
		VkPipelineMultisampleStateCreateInfo m_multisampling={};
		VkPipelineColorBlendAttachmentState m_colorBlendAttachment={};
		VkPipelineColorBlendStateCreateInfo m_colorBlending={};
		std::vector<VkDynamicState> m_dynamicStates;
		VkPipelineDynamicStateCreateInfo m_dynamicState={};

		//Mesh
		VkVertexInputBindingDescription m_inputBindingDescription={};
		std::vector<VkVertexInputAttributeDescription> m_attributeDescriptions;

		//Descriptors
		std::vector<VkDescriptorSetLayoutBinding> m_layoutBindings;

		//Vulkan objects
		VkRenderPass m_renderpass=VK_NULL_HANDLE;
		VK_Device* m_device=nullptr;
		VkDescriptorSetLayout m_descriptorSetLayout = VK_NULL_HANDLE;
		VkPipelineLayout m_pipelineLayout=VK_NULL_HANDLE;
		VkPipeline m_graphicsPipeline=VK_NULL_HANDLE;
	};

}