#include "VK_Shader.h"

#include "src/renderSystem/RenderSystem.h"

#include "src/vulkanObjects/VK_Device.h"

namespace Fierce {

	VK_Shader::VK_Shader(VK_Device* device, BinaryFileReader* reader) {
		m_device = device;
		m_reader = reader;

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
		delete m_sourceCode;

		m_device->debug_setName(VK_OBJECT_TYPE_SHADER_MODULE, (uint64_t)m_shaderModule, shaderName.c_str());
	}

	void VK_Shader::setSourceCode(std::string name) {
		if (!m_reader->openFile(name)) {
			RenderSystem::LOGGER->error("Failed to open shader file %s.", name.c_str());
		}
		long size = 0;
		if (!m_reader->readBinary(&size, nullptr)) {
			RenderSystem::LOGGER->error("Failed to read shader file %s.", name.c_str());
		}
		m_sourceCode = new char[size];
		if (!m_reader->readBinary(&size, &m_sourceCode)) {
			RenderSystem::LOGGER->error("Failed to read shader file %s.", name.c_str());
		}
		m_reader->closeFile();

		m_createInfo.codeSize = size;
		m_createInfo.pCode = reinterpret_cast<const uint32_t*>(m_sourceCode);
	}

}//end namespace