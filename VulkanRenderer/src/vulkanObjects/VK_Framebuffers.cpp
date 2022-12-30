#include "VK_Framebuffers.h"

#include "VK_Device.h"
#include "VK_Swapchain.h"
#include "VK_Renderpass.h"

VK_Framebuffers::VK_Framebuffers(VK_Device* device, VK_Swapchain* swapchain) {
    m_device = device;
    m_swapchain = swapchain;
    framebuffers.resize(swapchain->getNumImages());
}

VK_Framebuffers::~VK_Framebuffers() {
    for (auto framebuffer : framebuffers) {
        vkDestroyFramebuffer(m_device->getDevice(), framebuffer, nullptr);
    }
}

void VK_Framebuffers::create(){
    for (int i = 0; i < framebuffers.size(); i++) {
        VkImageView attachments[] = {
            m_swapchain->getImage(i)
        };

        VkFramebufferCreateInfo framebufferInfo{};
        framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.pNext = nullptr;
        framebufferInfo.flags = 0;
        LOGGER->info("Checking");
        framebufferInfo.renderPass = m_renderpass->getRenderpass();
        framebufferInfo.attachmentCount = 1;
        framebufferInfo.pAttachments = attachments;
        framebufferInfo.width = m_device->getSurfaceData()->swapchainWidth;
        framebufferInfo.height = m_device->getSurfaceData()->swapchainHeight;
        framebufferInfo.layers = 1;

        CHECK_VK(vkCreateFramebuffer(m_device->getDevice(), &framebufferInfo, nullptr, &framebuffers[i]), "Failed to create framebuffer.");
    }
}