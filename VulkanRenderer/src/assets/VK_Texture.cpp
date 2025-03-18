#include "VK_Texture.h"

#include "src/vulkanObjects/VK_Device.h"
#include "src/vulkanObjects/VK_Image.h"
#include "src/vulkanObjects/VK_ImageView.h"
#include "src/vulkanObjects/VK_Sampler.h"
#include "src/vulkanObjects/VK_DescriptorPool.h"

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
		delete m_descriptorSet;
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
		m_imageView = new VK_ImageView(m_device->getDevice(), m_image->getId(), VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_ASPECT_COLOR_BIT);
		m_imageView->create();
		m_device->debug_setName(VK_OBJECT_TYPE_IMAGE_VIEW, (uint64_t)m_imageView->getId(), "ImageView texture");

		m_sampler = new VK_Sampler(m_device);
		m_sampler->create();
		m_device->debug_setName(VK_OBJECT_TYPE_SAMPLER, (uint64_t)m_sampler->getId(), "Sampler texture");
	}

	void VK_Texture::createDescriptorSet(VK_DescriptorPool* descriptorPool, VkDescriptorSetLayout descriptorSetLayout){
		m_descriptorSet = new VK_DescriptorSet(m_device->getDevice(), descriptorPool->getId(), descriptorSetLayout);
		m_descriptorSet->create();
	}
	
	void VK_Texture::update(VK_Buffer* buffer, uint32_t binding) {
		m_descriptorSet->update(buffer, binding);
	}

	void VK_Texture::update(VK_Buffer* buffer) {
		m_descriptorSet->update(buffer);
	}

	void VK_Texture::update(VkImageView imageView, VkSampler imageSampler) {
		m_descriptorSet->update(imageView, imageSampler);
	}

	void VK_Texture::update(VK_Buffer* buffer, VkImageView imageView, VkSampler imageSampler) {
		m_descriptorSet->update(buffer, imageView, imageSampler);
	}
}//end namespace