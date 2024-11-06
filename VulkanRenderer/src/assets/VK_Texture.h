#pragma once

#include "vulkan/vulkan.h"

namespace Fierce {

	class VK_Device;
	class VK_Buffer;
	class VK_Image;
	class VK_ImageView;
	class VK_Sampler;

	class VK_Texture {
	public:
		VK_Texture(VK_Device* device, int width,int height,int numChannels);
		~VK_Texture();

		void loadData(int size,unsigned char* data);
		void swapBuffers(VK_Buffer*& buffer, VK_Image*& image);
		void createImageViewAndSampler();

		int getWidth() {return m_width;}
		int getHeight() { return m_height; }
		int getNumChannels() { return m_numChannels; }
		int getSize() { return m_width * m_height * m_numChannels; }

		VK_Buffer* getBuffer() { return m_buffer; }
		VK_Image* getImage() { return m_image; }
		VK_ImageView* getImageView() { return m_imageView; }
		VK_Sampler* getSampler() { return m_sampler; }

	private:
		VK_Device* m_device=nullptr;
		VK_Buffer* m_buffer=nullptr;
		VK_Image* m_image=nullptr;
		VK_ImageView* m_imageView = nullptr;
		VK_Sampler* m_sampler = nullptr;

		int m_width=0;
		int m_height = 0;
		int m_numChannels = 0;
	};
}//end namespace