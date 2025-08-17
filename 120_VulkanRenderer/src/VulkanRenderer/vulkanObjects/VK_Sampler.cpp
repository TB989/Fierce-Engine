#include "VK_Sampler.h"

#include "src/VulkanRenderer/vulkanObjects/VK_Device.h"

#include "src/VulkanRenderer/renderSystem/RenderSystem.h"

namespace Fierce {
	VK_Sampler::VK_Sampler(VK_Device* device){
		m_device = device;

		m_createInfo = {};
		m_createInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
		m_createInfo.pNext = nullptr;
		m_createInfo.flags = 0;
		m_createInfo.magFilter = VK_FILTER_LINEAR;
		m_createInfo.minFilter = VK_FILTER_LINEAR;
		m_createInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
		m_createInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
		m_createInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
		m_createInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
		m_createInfo.unnormalizedCoordinates = VK_FALSE;
		m_createInfo.compareEnable = VK_FALSE;
		m_createInfo.compareOp = VK_COMPARE_OP_ALWAYS;
		m_createInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
		m_createInfo.mipLodBias = 0.0f;
		m_createInfo.minLod = 0.0f;
		m_createInfo.maxLod = 0.0f;
	}

	VK_Sampler::~VK_Sampler(){
		vkDestroySampler(m_device->getDevice(),m_sampler,nullptr);
	}

	void VK_Sampler::create(){
		if (m_device->supportsSamplerAnisotropy()) {
			RenderSystem::LOGGER->info("Activated sampler anisotropy with %1.3f", m_device->getDeviceData()->deviceProperties.limits.maxSamplerAnisotropy);
			m_createInfo.anisotropyEnable = VK_TRUE;
			m_createInfo.maxAnisotropy = m_device->getDeviceData()->deviceProperties.limits.maxSamplerAnisotropy;
		}
		else {
			m_createInfo.anisotropyEnable = VK_FALSE;
			m_createInfo.maxAnisotropy = 1.0f;
		}

		if (vkCreateSampler(m_device->getDevice(), &m_createInfo, nullptr, &m_sampler) != VK_SUCCESS) {
			RenderSystem::LOGGER->error("Failed to create sampler.");
		}
	}
}//end namespace