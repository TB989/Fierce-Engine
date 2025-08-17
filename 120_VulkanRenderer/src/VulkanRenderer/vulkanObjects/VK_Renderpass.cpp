#include "VK_Renderpass.h"

#include "VK_Device.h"

#include "src/VulkanRenderer/renderSystem/RenderSystem.h"

#include <array>

namespace Fierce {

	VK_Renderpass::VK_Renderpass(VK_Device* device){
		m_device = device;

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

		m_depthAttachmentDescription = {};
		m_depthAttachmentDescription.flags = 0;
		m_depthAttachmentDescription.format = device->getSurfaceData()->depthFormat;
		m_depthAttachmentDescription.samples = VK_SAMPLE_COUNT_1_BIT;
		m_depthAttachmentDescription.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		m_depthAttachmentDescription.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		m_depthAttachmentDescription.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		m_depthAttachmentDescription.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		m_depthAttachmentDescription.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		m_depthAttachmentDescription.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

		m_depthAttachmentReference = {};
		m_depthAttachmentReference.attachment = 1;
		m_depthAttachmentReference.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

		m_subpassDependency = {};
		m_subpassDependency.dependencyFlags = 0;
		m_subpassDependency.srcSubpass = VK_SUBPASS_EXTERNAL;
		m_subpassDependency.dstSubpass = 0;

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
		m_renderPassCreateInfo.subpassCount = 1;
		m_renderPassCreateInfo.pSubpasses = &m_subpassDescription;
		m_renderPassCreateInfo.dependencyCount = 1;
		m_renderPassCreateInfo.pDependencies = &m_subpassDependency;
	}

	VK_Renderpass::~VK_Renderpass(){
		vkDestroyRenderPass(m_device->getDevice(), m_renderPass, nullptr);
	}

	void VK_Renderpass::addDepthBuffer(){
		m_hasDepthBuffer = true;
	}

	void VK_Renderpass::create(){
		if (m_hasDepthBuffer) {
			m_subpassDescription.pDepthStencilAttachment = &m_depthAttachmentReference;

			std::array<VkAttachmentDescription, 2> attachments= { m_colorAttachmentDescription, m_depthAttachmentDescription };

			m_renderPassCreateInfo.attachmentCount = 2;
			m_renderPassCreateInfo.pAttachments = attachments.data();

			m_subpassDependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
			m_subpassDependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
			m_subpassDependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
		}
		else {
			m_renderPassCreateInfo.attachmentCount = 1;
			m_renderPassCreateInfo.pAttachments = &m_colorAttachmentDescription;

			m_subpassDependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
			m_subpassDependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
			m_subpassDependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_COLOR_ATTACHMENT_READ_BIT;
		}


		if (vkCreateRenderPass(m_device->getDevice(), &m_renderPassCreateInfo, nullptr, &m_renderPass) != VK_SUCCESS) {
			RenderSystem::LOGGER->error("Failed to create renderpass.");
		}

		m_device->debug_setName(VK_OBJECT_TYPE_RENDER_PASS, (uint64_t)m_renderPass, "Renderpass");
	}

}//end namespace