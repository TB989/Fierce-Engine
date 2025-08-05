#include "VulkanGraphicsContetxt.h"

#include "src/vulkanObjects/VK_Buffer.h"

#include "src/Color.h"

#include "src/renderSystem/RenderSystem.h"

namespace Fierce {
	VulkanGraphicsContext::VulkanGraphicsContext(VK_Device* device){
		m_activeColor = new Color3f(1.0f,1.0f,1.0f);

		m_fonts = new VK_Manager<Font*>();

		m_device = device;

		//Buffers colored rectangles
		m_vertexBuffer = new VK_Buffer(device, VERTEX_BUFFER_SIZE * sizeof(float), VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
		m_vertexBuffer->setKeepMapped(true);
		m_vertexBuffer->create();
		m_indexBuffer = new VK_Buffer(device, INDEX_BUFFER_SIZE * sizeof(uint16_t), VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
		m_indexBuffer->setKeepMapped(true);
		m_indexBuffer->create();
		m_vertices = (float*)m_vertexBuffer->getMappedMemoryRegion();
		m_indices = (uint16_t*)m_indexBuffer->getMappedMemoryRegion();

		//Buffers font
		m_vertexBufferFont = new VK_Buffer(device, VERTEX_BUFFER_SIZE_FONT * sizeof(float), VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
		m_vertexBufferFont->setKeepMapped(true);
		m_vertexBufferFont->create();
		m_indexBufferFont = new VK_Buffer(device, INDEX_BUFFER_SIZE_FONT * sizeof(uint16_t), VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
		m_indexBufferFont->setKeepMapped(true);
		m_indexBufferFont->create();
		m_verticesFont = (float*)m_vertexBufferFont->getMappedMemoryRegion();
		m_indicesFont = (uint16_t*)m_indexBufferFont->getMappedMemoryRegion();
	}

	VulkanGraphicsContext::~VulkanGraphicsContext(){
		delete m_vertexBuffer;
		delete m_indexBuffer;

		delete m_vertexBufferFont;
		delete m_indexBufferFont;

		delete m_fonts;

		delete m_activeColor;
	}

	void VulkanGraphicsContext::reset(){
		m_vertexPointer = 0;
		m_indexPointer = 0;
		m_numRectangles = 0;

		m_vertexPointerFont = 0;
		m_indexPointerFont = 0;
		m_numFontRectangles = 0;
	}

	void VulkanGraphicsContext::setColor(int r, int g, int b){
		m_activeColor->setR((float)r / 255.0f);
		m_activeColor->setG((float)g / 255.0f);
		m_activeColor->setB((float)b / 255.0f);
	}

	void VulkanGraphicsContext::setFont(std::string font,int size){
		m_activeFont = m_fonts->get(font);
		m_activeFontSize = size;
	}

	void VulkanGraphicsContext::drawRect(int x, int y, int width, int height){
		putIndex(4*m_numRectangles); putIndex(4 * m_numRectangles + 1); putIndex(4 * m_numRectangles + 2);
		putIndex(4 * m_numRectangles); putIndex(4 * m_numRectangles + 2); putIndex(4 * m_numRectangles + 3);

		putVertex(x); putVertex(y);
		putVertex(m_activeColor->getR()); putVertex(m_activeColor->getG()); putVertex(m_activeColor->getB());
		putVertex(x); putVertex(y+height);
		putVertex(m_activeColor->getR()); putVertex(m_activeColor->getG()); putVertex(m_activeColor->getB());
		putVertex(x+width); putVertex(y+height);
		putVertex(m_activeColor->getR()); putVertex(m_activeColor->getG()); putVertex(m_activeColor->getB());
		putVertex(x+width); putVertex(y);
		putVertex(m_activeColor->getR()); putVertex(m_activeColor->getG()); putVertex(m_activeColor->getB());

		m_numRectangles++;
	}

	void VulkanGraphicsContext::drawText(int x, int y, std::string text){
		char letter;
		Font::Char character;
		int padding = m_activeFont->info.padding[0];
		float cursor = 0.0f;
		int kerning = 0;
		
		for (int i = 0; i < text.size(); i++) {
			letter = text[i];
			character = m_activeFont->chars.chars[letter];

			//Search for kerning
			if (i<text.size()-1) {
				for (int j = 0; j < m_activeFont->kernings.count; j++) {
					Font::Kerning kern = m_activeFont->kernings.kernings[j];
					if (kern.first == text[i]&& kern.second == text[i+1]) {
						kerning = kern.amount;
					}
				}
			}

			//Texture coordinates
			float u1 = (float)character.x / (float)m_activeFont->common.scaleW;
			float u2 = (float)(character.x + character.width) / (float)m_activeFont->common.scaleW;
			float v1 = (float)character.y / (float)m_activeFont->common.scaleH;
			float v2 = (float)(character.y + character.height) / (float)m_activeFont->common.scaleH;

			//Positions
			float x1 = cursor + (float)x + (float)(character.xoffset);
			float x2 = cursor + (float)x + (float)(character.xoffset) + (float)character.width;
			float y1 = (float)y + (float)(character.yoffset)-2*padding;
			float y2 = (float)y + (float)(character.yoffset) + (float)character.height-2*padding;
			cursor += (float)character.xadvance - 2.5f * padding +kerning;

			//Put Indices
			putFontIndex(4 * m_numFontRectangles); putFontIndex(4 * m_numFontRectangles + 1); putFontIndex(4 * m_numFontRectangles + 2);
			putFontIndex(4 * m_numFontRectangles); putFontIndex(4 * m_numFontRectangles + 2); putFontIndex(4 * m_numFontRectangles + 3);

			//Put vertices
			putFontVertex(x1); putFontVertex(y1); putFontVertex(u1); putFontVertex(v1);
			putFontVertex(m_activeColor->getR()); putFontVertex(m_activeColor->getG()); putFontVertex(m_activeColor->getB());
			putFontVertex(x1); putFontVertex(y2); putFontVertex(u1); putFontVertex(v2);
			putFontVertex(m_activeColor->getR()); putFontVertex(m_activeColor->getG()); putFontVertex(m_activeColor->getB());
			putFontVertex(x2); putFontVertex(y2); putFontVertex(u2); putFontVertex(v2);
			putFontVertex(m_activeColor->getR()); putFontVertex(m_activeColor->getG()); putFontVertex(m_activeColor->getB());
			putFontVertex(x2); putFontVertex(y1); putFontVertex(u2); putFontVertex(v1);
			putFontVertex(m_activeColor->getR()); putFontVertex(m_activeColor->getG()); putFontVertex(m_activeColor->getB());

			m_numFontRectangles++;
			kerning = 0;
		}
	}

	void VulkanGraphicsContext::addFont(std::string name,Font* font){
		m_fonts->add(name, font);
	}

	void VulkanGraphicsContext::putIndex(uint16_t index){
		m_indices[m_indexPointer] = index;
		m_indexPointer++;
	}

	void VulkanGraphicsContext::putVertex(float vertex){
		m_vertices[m_vertexPointer] = vertex;
		m_vertexPointer++;
	}

	void VulkanGraphicsContext::putFontIndex(uint16_t index){
		m_indicesFont[m_indexPointerFont] = index;
		m_indexPointerFont++;
	}

	void VulkanGraphicsContext::putFontVertex(float vertex){
		m_verticesFont[m_vertexPointerFont] = vertex;
		m_vertexPointerFont++;
	}
}