#pragma once

#include "vulkan/vulkan.h"

namespace Fierce {

	class VK_Device;

	class VK_Pipeline {
	public:
		VK_Pipeline(VK_Device* device,VkRenderPass renderpass);
		~VK_Pipeline();

		void create();
		VkPipeline getId() { return m_graphicsPipeline; }
		VkPipelineLayout getLayout() { return m_pipelineLayout; }

	public:
		void addVertexShader(VkShaderModule shader);
		void addFragmentShader(VkShaderModule shader);

	private:
		//Create info
		VkGraphicsPipelineCreateInfo m_createInfo={};
		VkPipelineLayoutCreateInfo m_pipelineLayoutInfo = {};

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

		//Vulkan objects
		VkRenderPass m_renderpass=VK_NULL_HANDLE;
		VK_Device* m_device=nullptr;
		VkPipelineLayout m_pipelineLayout=VK_NULL_HANDLE;
		VkPipeline m_graphicsPipeline=VK_NULL_HANDLE;
	};

}