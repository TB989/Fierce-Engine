#pragma once

#include "vulkan/vulkan.h"

namespace Fierce {

	class VK_Device;
	class VK_CommandBuffer;
	class VK_Buffer;
	class VK_Image;

	class UploadContext {
	public:
		UploadContext(VK_Device* device);
		~UploadContext();

		void copyBuffer(VK_Buffer* source, VK_Buffer* destination,VkDeviceSize size);
		void copyImage(VK_Buffer* source,VK_Image* destination,uint32_t width,uint32_t height);

		void startAndWaitForUpload();

	private:
		VK_Device* m_device;
		VK_CommandBuffer* m_transferCommandBuffer = nullptr;
		VK_CommandBuffer* m_graphicsCommandBuffer = nullptr;
	};
}//end namespace