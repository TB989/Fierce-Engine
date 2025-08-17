#pragma once

#include "vulkan/vulkan.h"

namespace Fierce {
	class VK_ImageView {
	public:
		VK_ImageView(VkDevice device,VkImage image,VkFormat format, VkImageAspectFlags aspectFlags);
		~VK_ImageView();

		void create();
		VkImageView getId() { return m_imageView; }

	private:
		//Create info
		VkImageViewCreateInfo m_createInfo={};

		//Vulkan objects
		VkDevice m_device=VK_NULL_HANDLE;
		VkImage m_image=VK_NULL_HANDLE;
		VkImageView m_imageView=VK_NULL_HANDLE;
	};
}//end namespace