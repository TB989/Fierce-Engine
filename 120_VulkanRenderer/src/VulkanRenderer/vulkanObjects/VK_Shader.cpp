#include "VK_Shader.h"

#include "src/VulkanRenderer/renderSystem/RenderSystem.h"

#include "src/VulkanRenderer/vulkanObjects/VK_Device.h"

namespace Fierce {

	VK_Shader::VK_Shader(VK_Device* device) {
		m_device = device;

		m_createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		m_createInfo.pNext = nullptr;
		m_createInfo.flags = 0;
	}

	VK_Shader::~VK_Shader() {
		vkDestroyShaderModule(m_device->getDevice(), m_shaderModule, nullptr);
	}

	void VK_Shader::create() {
		if (vkCreateShaderModule(m_device->getDevice(), &m_createInfo, nullptr, &m_shaderModule) != VK_SUCCESS) {
			RenderSystem::LOGGER->error("Failed to create shader module.");
		}
	}

	void VK_Shader::setSourceCode(size_t size, char* sourceCode) {
		m_createInfo.codeSize = size;
		m_createInfo.pCode = reinterpret_cast<const uint32_t*>(sourceCode);
	}

}//end namespace