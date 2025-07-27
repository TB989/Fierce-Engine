#include "VulkanGraphicsContetxt.h"

#include "src/vulkanObjects/VK_Buffer.h"

#include "src/Color.h"

namespace Fierce {
	VulkanGraphicsContext::VulkanGraphicsContext(VK_Device* device){
		m_color = new Color3f(1.0f,1.0f,1.0f);

		m_device = device;
		m_vertexBuffer = new VK_Buffer(device, VERTEX_BUFFER_SIZE * sizeof(float), VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
		m_vertexBuffer->setKeepMapped(true);
		m_vertexBuffer->create();
		m_indexBuffer = new VK_Buffer(device, INDEX_BUFFER_SIZE * sizeof(uint16_t), VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
		m_indexBuffer->setKeepMapped(true);
		m_indexBuffer->create();
		m_vertices = (float*)m_vertexBuffer->getMappedMemoryRegion();
		m_indices = (uint16_t*)m_indexBuffer->getMappedMemoryRegion();
	}

	VulkanGraphicsContext::~VulkanGraphicsContext(){
		delete m_vertexBuffer;
		delete m_indexBuffer;

		delete m_color;
	}

	void VulkanGraphicsContext::reset(){
		m_vertexPointer = 0;
		m_indexPointer = 0;
		m_numRectangles = 0;
	}

	void VulkanGraphicsContext::setColor(int r, int g, int b){
		m_color->setR((float)r / 255.0f);
		m_color->setG((float)g / 255.0f);
		m_color->setB((float)b / 255.0f);
	}

	void VulkanGraphicsContext::setFont(std::string font){

	}

	void VulkanGraphicsContext::drawRect(int x, int y, int width, int height){
		putIndex(4*m_numRectangles); putIndex(4 * m_numRectangles + 1); putIndex(4 * m_numRectangles + 2);
		putIndex(4 * m_numRectangles); putIndex(4 * m_numRectangles + 2); putIndex(4 * m_numRectangles + 3);

		putVertex(x); putVertex(y);
		putVertex(m_color->getR()); putVertex(m_color->getG()); putVertex(m_color->getB());
		putVertex(x); putVertex(y+height);
		putVertex(m_color->getR()); putVertex(m_color->getG()); putVertex(m_color->getB());
		putVertex(x+width); putVertex(y+height);
		putVertex(m_color->getR()); putVertex(m_color->getG()); putVertex(m_color->getB());
		putVertex(x+width); putVertex(y);
		putVertex(m_color->getR()); putVertex(m_color->getG()); putVertex(m_color->getB());

		m_numRectangles++;
	}

	void VulkanGraphicsContext::drawText(int x, int y, std::string text){
		
	}

	void VulkanGraphicsContext::loadFonts(){

	}

	void VulkanGraphicsContext::putIndex(uint16_t index){
		m_indices[m_indexPointer] = index;
		m_indexPointer++;
	}
	void VulkanGraphicsContext::putVertex(float vertex){
		m_vertices[m_vertexPointer] = vertex;
		m_vertexPointer++;
	}
}