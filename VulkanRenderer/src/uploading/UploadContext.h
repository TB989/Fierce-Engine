#pragma once

namespace Fierce {

	class VK_CommandPool;
	class VK_CommandBuffer;

	class UploadContext {
	public:
		UploadContext();
		~UploadContext();

	private:
		VK_CommandPool* m_copyCommandPool = nullptr;
		VK_CommandBuffer* m_copyCommandBuffer = nullptr;
	};
}//end namespace