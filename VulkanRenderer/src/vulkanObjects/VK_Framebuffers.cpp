#include "VK_Framebuffers.h"

#include "VK_Device.h"
#include "VK_Swapchain.h"
#include "VK_Renderpass.h"

VK_Framebuffers::VK_Framebuffers(VK_Device* device, VK_Swapchain* swapchain, VK_Renderpass* renderpass) {
    m_device = device->getDevice();
    framebuffers.resize(swapchain->getNumImages());

    for (int i = 0; i < framebuffers.size(); i++) {
        VkImageView attachments[] = {
            swapchain->getImage(i)
        };

        VkFramebufferCreateInfo framebufferInfo{};
        framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.pNext = nullptr;
        framebufferInfo.flags = 0;
        framebufferInfo.renderPass = renderpass->getRenderpass();
        framebufferInfo.attachmentCount = 1;
        framebufferInfo.pAttachments = attachments;
        framebufferInfo.width = device->getSurfaceData()->swapchainWidth;
        framebufferInfo.height = device->getSurfaceData()->swapchainHeight;
        framebufferInfo.layers = 1;

        CHECK_VK(vkCreateFramebuffer(m_device, &framebufferInfo, nullptr, &framebuffers[i]), "Failed to create framebuffer.");
    }
}

VK_Framebuffers::~VK_Framebuffers() {
    for (auto framebuffer : framebuffers) {
        vkDestroyFramebuffer(m_device, framebuffer, nullptr);
    }
}