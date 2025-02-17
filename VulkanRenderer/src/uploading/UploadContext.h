#pragma once

#include "vulkan/vulkan.h"

#include <vector>

namespace Fierce {

	class VK_Device;
	class VK_CommandBuffer;
	class VK_Buffer;
	class VK_Image;
	class VK_Mesh;
	class VK_Texture;

	class UploadContext {
	public:
		UploadContext(VK_Device* device);
		~UploadContext();

		void copyBuffer(VK_Buffer* source, VK_Buffer* destination,VkDeviceSize size);
		void copyImage(VK_Buffer* source,VK_Image* destination,uint32_t width,uint32_t height);

		void copyMesh(VK_Mesh* mesh);
		void copyTexture(VK_Texture* texture);

		void transitionImageLayout(VkImage image,VkImageLayout oldLayout,VkImageLayout newLayout);

		void startAndWaitForUpload();

	private:
		VK_Device* m_device;
		VK_CommandBuffer* m_transferCommandBuffer = nullptr;
		VK_CommandBuffer* m_graphicsCommandBuffer = nullptr;

		std::vector<VK_Buffer*> m_buffersToDelete;
	};
}//end namespace