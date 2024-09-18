#include "VK_Renderpass.h"

#include "VK_Device.h"

#include "renderSystem/RenderSystem.h"

namespace Fierce {

	VK_Renderpass::VK_Renderpass(VK_Device* device){
		m_device = device->getDevice();

		m_colorAttachmentDescription = {};
		m_colorAttachmentDescription.flags = 0;
		m_colorAttachmentDescription.format = device->getSurfaceData()->swapchainFormat.format;
		m_colorAttachmentDescription.samples = VK_SAMPLE_COUNT_1_BIT;
		m_colorAttachmentDescription.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		m_colorAttachmentDescription.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
		m_colorAttachmentDescription.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		m_colorAttachmentDescription.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		m_colorAttachmentDescription.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		m_colorAttachmentDescription.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

		m_colorAttachmentReference ={};
		m_colorAttachmentReference.attachment = 0;
		m_colorAttachmentReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

		m_subpassDependency = {};
		m_subpassDependency.dependencyFlags = 0;
		m_subpassDependency.srcSubpass = VK_SUBPASS_EXTERNAL;
		m_subpassDependency.dstSubpass = 0;
		m_subpassDependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		m_subpassDependency.srcAccessMask = 0;
		m_subpassDependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		m_subpassDependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_COLOR_ATTACHMENT_READ_BIT;

		m_subpassDescription={};
		m_subpassDescription.flags = 0;
		m_subpassDescription.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
		m_subpassDescription.inputAttachmentCount = 0;
		m_subpassDescription.pInputAttachments = nullptr;
		m_subpassDescription.colorAttachmentCount = 1;
		m_subpassDescription.pColorAttachments = &m_colorAttachmentReference;
		m_subpassDescription.pResolveAttachments = nullptr;
		m_subpassDescription.pDepthStencilAttachment = nullptr;
		m_subpassDescription.preserveAttachmentCount = 0;
		m_subpassDescription.pPreserveAttachments = nullptr;

		m_renderPassCreateInfo = {};
		m_renderPassCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		m_renderPassCreateInfo.pNext = nullptr;
		m_renderPassCreateInfo.flags = 0;
		m_renderPassCreateInfo.attachmentCount = 1;
		m_renderPassCreateInfo.pAttachments = &m_colorAttachmentDescription;
		m_renderPassCreateInfo.subpassCount = 1;
		m_renderPassCreateInfo.pSubpasses = &m_subpassDescription;
		m_renderPassCreateInfo.dependencyCount = 1;
		m_renderPassCreateInfo.pDependencies = &m_subpassDependency;
	}

	VK_Renderpass::~VK_Renderpass(){
		vkDestroyRenderPass(m_device, m_renderPass, nullptr);
	}

	void VK_Renderpass::create(){
		if (vkCreateRenderPass(m_device, &m_renderPassCreateInfo, nullptr, &m_renderPass)!=VK_SUCCESS) {
			RenderSystem::LOGGER->error("Failed to create renderpass.");
		}
	}

}//end namespace