#pragma once

#include "src/Common.h"
#include "VulkanObject.h"

class VK_Device;
class VK_Shader;
class VK_Renderpass;

class VK_Pipeline:public VulkanObject {
public:
	VK_Pipeline(VK_Device* device, VK_Shader* vertexShader, VK_Shader* fragmentShader);
	~VK_Pipeline();

	void create();
	
	void addRenderPass(VK_Renderpass* renderpass) { m_renderpass = renderpass; }

	VkPipeline getPipeline() { return graphicsPipeline; }
	VkPipelineLayout getPipelineLayout() { return pipelineLayout; }
	VkDescriptorSetLayout getDescLayout() { return descriptorSetLayout; }

private:
	VkDevice m_device;
	VK_Renderpass* m_renderpass;

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

	VkDescriptorSetLayout descriptorSetLayout;

private:
	void createShaderStages(VK_Shader* vertexShader, VK_Shader* fragmentShader);
	void createVertexInput();
	void createInputAssembly();
	void createViewportScissor(VK_Device* device);
	void createRasterizer();
	void createMultisampling();
	void createColorBlending();
	void createPipeline();
};