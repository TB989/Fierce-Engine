#include "VK_Texture.h"

#include "vulkanObjects/VK_Device.h"
#include "vulkanObjects/VK_Buffer.h"
#include "vulkanObjects/VK_Image.h"
#include "vulkanObjects/VK_ImageView.h"
#include "vulkanObjects/VK_Sampler.h"

namespace Fierce {
	VK_Texture::VK_Texture(VK_Device* device, int width, int height, int numChannels){
		m_device = device;
		m_width = width;
		m_height = height;
		m_numChannels = numChannels;
		m_buffer = new VK_Buffer(device, width*height*numChannels, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
		m_buffer->create();
	}

	VK_Texture::~VK_Texture(){
		if (m_buffer!=nullptr) {
			delete m_buffer;
		}
		if (m_image != nullptr) {
			delete m_image;
		}
		delete m_imageView;
		delete m_sampler;
	}

	void VK_Texture::loadData(int size, unsigned char* pixels){
		m_buffer->loadData(size, pixels);
	}

	void VK_Texture::swapBuffers(VK_Buffer*& buffer, VK_Image*& image) {
		VK_Buffer* tempBuffer = m_buffer;
		VK_Image* tempImage = m_image;

		m_buffer = buffer;
		m_image = image;
		buffer = tempBuffer;
		image = tempImage;
	}

	void VK_Texture::createImageViewAndSampler(){
		m_imageView = new VK_ImageView(m_device->getDevice(), m_image->getId());
		m_imageView->create();
		m_device->debug_setName(VK_OBJECT_TYPE_IMAGE_VIEW, (uint64_t)m_imageView->getId(), "ImageView texture");

		m_sampler = new VK_Sampler(m_device);
		m_sampler->create();
		m_device->debug_setName(VK_OBJECT_TYPE_SAMPLER, (uint64_t)m_sampler->getId(), "Sampler texture");
	}
}//end namespace