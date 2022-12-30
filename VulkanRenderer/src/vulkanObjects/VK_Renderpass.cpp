#include "VK_Renderpass.h"

#include "VK_Device.h"

VK_Renderpass::VK_Renderpass(VK_Device* device) {
    m_device = device;

    //Add dependencies for VK_SUBPASS_EXTERNAL
    VkSubpassDependency dependencyIn{};
    dependencyIn.dependencyFlags = 0;
    dependencyIn.srcSubpass = VK_SUBPASS_EXTERNAL;
    dependencyIn.dstSubpass = 0;
    dependencyIn.srcStageMask = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
    dependencyIn.srcAccessMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependencyIn.dstStageMask = VK_ACCESS_MEMORY_READ_BIT;
    dependencyIn.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    dependencies.push_back(dependencyIn);

    VkSubpassDependency dependencyOut{};
    dependencyOut.dependencyFlags = 0;
    dependencyOut.srcSubpass = 0;
    dependencyOut.dstSubpass = VK_SUBPASS_EXTERNAL;
    dependencyOut.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependencyOut.srcAccessMask = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
    dependencyOut.dstStageMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    dependencyOut.dstAccessMask = VK_ACCESS_MEMORY_READ_BIT;
    dependencies.push_back(dependencyOut);
}

VK_Renderpass::~VK_Renderpass() {
    vkDestroyRenderPass(m_device->getDevice(), renderPass, nullptr);
}

void VK_Renderpass::addColorAttachment(VkFormat format, bool isSwapchainAttachment){
    addColorAttachment(format,isSwapchainAttachment,VK_SAMPLE_COUNT_1_BIT);
}

void VK_Renderpass::addColorAttachment(VkFormat format, bool isSwapchainAttachment, VkSampleCountFlagBits sampleCount){
    VkAttachmentDescription attachment{};
    attachment.flags = 0;
    attachment.format = format;
    attachment.samples = sampleCount;
    attachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    if (isSwapchainAttachment) {
        attachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    }
    else {
        attachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    }
    attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    attachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    if (isSwapchainAttachment) {
        attachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
    }
    else {
        attachment.finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    }
    attachments.push_back(attachment);
    numAttachments++;
}

void VK_Renderpass::addDepthAttachment(VkFormat format){
    addDepthAttachment(format,VK_SAMPLE_COUNT_1_BIT);
}

void VK_Renderpass::addDepthAttachment(VkFormat format, VkSampleCountFlagBits sampleCount){
    VkAttachmentDescription attachment{};
    attachment.flags = 0;
    attachment.format = format;
    attachment.samples = sampleCount;
    attachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    attachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    attachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    attachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
    attachments.push_back(attachment);
    numAttachments++;
}

void VK_Renderpass::addSubpass(uint32_t numDepthAttachments, uint32_t numColorAttachments, uint32_t numInputAttachments, uint32_t numResolveAttachments, uint32_t numPreserveAttachments, uint32_t attachments[]) {
    SubpassReferences refs = {};
    VkSubpassDescription subpass{};
    subpass.flags = 0;
    subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;

    uint32_t counter = 0;

    //Depth attachments
    if (numDepthAttachments == 1) {
        VkAttachmentReference depthRef = {};
        depthRef.attachment = attachments[counter];
        counter++;
        depthRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
        refs.depthAttachmentReference = depthRef;

        subpass.pDepthStencilAttachment = &depthRef;
    }
    else if(numDepthAttachments==0) {
        subpass.pDepthStencilAttachment = nullptr;
    }
    else {
        LOGGER->warn("Only one depth attachment suppported for subpass.");
        subpass.pDepthStencilAttachment = nullptr;
    }

    //Color attachments
    if (numColorAttachments > 0) {
        for (uint32_t i=0; i < numColorAttachments; i++) {
            VkAttachmentReference colorRef = {};
            colorRef.attachment = attachments[counter];
            counter++;
            colorRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
            refs.colorAttachmentReferences.push_back(colorRef);
        }
        subpass.colorAttachmentCount = numColorAttachments;
        subpass.pColorAttachments = refs.colorAttachmentReferences.data();
    }
    else {
        subpass.colorAttachmentCount = 0;
        subpass.pColorAttachments = nullptr;
    }

    //Input attachments
    if (numInputAttachments > 0) {
        for (uint32_t i=0; i < numInputAttachments; i++) {
            VkAttachmentReference inputRef = {};
            inputRef.attachment = attachments[counter];
            counter++;
            inputRef.layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
            refs.inputAttachmentReferences.push_back(inputRef);
        }
        subpass.inputAttachmentCount = numInputAttachments;
        subpass.pInputAttachments = refs.inputAttachmentReferences.data();
    }
    else {
        subpass.inputAttachmentCount = 0;
        subpass.pInputAttachments = nullptr;
    }

    //TODO: Preserve attachments
    /*if (numPreserveAttachments > 0) {
        subpass.preserveAttachmentCount = numPreserveAttachments;
        subpass.pPreserveAttachments = preserveAttachments;
    }
    else {
        subpass.preserveAttachmentCount = 0;
        subpass.pPreserveAttachments = nullptr;
    }*/

    //Resolve attachments
    if (numResolveAttachments >= 0) {
        VkAttachmentReference resolveRef = {};
        resolveRef.attachment = attachments[counter];
        resolveRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
        refs.resolveReference = resolveRef;

        subpass.pResolveAttachments = &resolveRef;
    }
    else {
        subpass.pResolveAttachments = nullptr;
    }

    subpasses.push_back(subpass);
    subpassReferences.push_back(refs);
}

void VK_Renderpass::addDependency(
    VkDependencyFlags srcSubpass, VkDependencyFlags dstSubpass,
    VkPipelineStageFlags srcStageFlags, VkPipelineStageFlags dstStageFlags,
    VkAccessFlags srcAccessMask,
    VkAccessFlags dstAccessMask)
{
    VkSubpassDependency dependency{};
    dependency.dependencyFlags = 0;
    dependency.srcSubpass = srcSubpass;
    dependency.dstSubpass = dstSubpass;
    dependency.srcStageMask = srcStageFlags;
    dependency.srcAccessMask = srcAccessMask;
    dependency.dstStageMask = dstStageFlags;
    dependency.dstAccessMask = dstAccessMask;
    dependencies.push_back(dependency);
}

void VK_Renderpass::create(){
    VkRenderPassCreateInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassInfo.flags = VK_DEPENDENCY_BY_REGION_BIT;
    renderPassInfo.pNext = nullptr;
    if (attachments.size()==0) {
        renderPassInfo.attachmentCount = 0;
        renderPassInfo.pAttachments = nullptr;
    }
    else {
        LOGGER->info("Adding attachments %i", attachments.size());
        LOGGER->info("%i", attachments[0].flags);
        LOGGER->info("%i", attachments[0].finalLayout);
        LOGGER->info("%i", attachments[0].format);
        LOGGER->info("%i", attachments[0].initialLayout);
        LOGGER->info("%i", attachments[0].samples);
        LOGGER->info("%i", attachments[0].loadOp);
        LOGGER->info("%i", attachments[0].storeOp);

        renderPassInfo.attachmentCount = attachments.size();
        renderPassInfo.pAttachments = attachments.data();
    }
    if (subpasses.size() == 0) {
        renderPassInfo.subpassCount = 0;
        renderPassInfo.pSubpasses = nullptr;
    }
    else {
        LOGGER->info("Adding subpasses %i", subpasses.size());
        renderPassInfo.subpassCount = subpasses.size();
        renderPassInfo.pSubpasses = subpasses.data();

        LOGGER->info("");
        LOGGER->info("%i", subpasses[0].flags);
        LOGGER->info("%i", subpasses[0].colorAttachmentCount);
        LOGGER->info("%i", subpasses[0].inputAttachmentCount);
        LOGGER->info("%i", subpasses[0].preserveAttachmentCount);
        LOGGER->info("%i", subpassReferences[0].colorAttachmentReferences[0].attachment);
        LOGGER->info("%i", subpassReferences[0].colorAttachmentReferences[0].layout);
    }
    if (dependencies.size() == 0) {
        renderPassInfo.dependencyCount = dependencies.size();
        renderPassInfo.pDependencies = dependencies.data();
    }
    else {
        LOGGER->info("Adding dependencies %i", dependencies.size());
        renderPassInfo.dependencyCount = 0;
        renderPassInfo.pDependencies = nullptr;
    }

    CHECK_VK(vkCreateRenderPass(m_device->getDevice(), &renderPassInfo, nullptr, &renderPass), "Failed to create render pass.");
}