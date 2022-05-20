#pragma once

#include "Common.h"

class VK_Device;
class VK_Shader;
class VK_Renderpass;

class VK_Pipeline {
public:
	VK_Pipeline(VK_Device* device, VK_Shader* vertexShader, VK_Shader* fragmentShader, VK_Renderpass* renderpass);
	~VK_Pipeline();

	VkPipeline getPipeline() { return graphicsPipeline; }

private:
	VkDevice m_device;

	VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
	VkPipelineShaderStageCreateInfo fragShaderStageInfo{};
	VkPipelineShaderStageCreateInfo shaderStages[2];

	VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
	VkPipelineInputAssemblyStateCreateInfo inputAssembly{};

	VkViewport viewport{};
	VkRect2D scissor{};
	VkPipelineViewportStateCreateInfo viewportState{};

	VkPipelineRasterizationStateCreateInfo rasterizer{};
	VkPipelineMultisampleStateCreateInfo multisampling{};
	VkPipelineColorBlendAttachmentState colorBlendAttachment{};
	VkPipelineColorBlendStateCreateInfo colorBlending{};

	VkPipelineLayout pipelineLayout;
	VkPipeline graphicsPipeline;

	VkVertexInputBindingDescription bindingDescription;
	std::vector<VkVertexInputAttributeDescription> attributes;
	VkVertexInputAttributeDescription desc1;
	VkVertexInputAttributeDescription desc2;

private:
	void createShaderStages(VK_Shader* vertexShader, VK_Shader* fragmentShader);
	void createVertexInput();
	void createInputAssembly();
	void createViewportScissor(VK_Device* device);
	void createRasterizer();
	void createMultisampling();
	void createColorBlending();
	void createPipeline(VkRenderPass renderpass);
};