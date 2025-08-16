#include "VulkanGraphicsContetxt.h"

#include "src/Color.h"

#include "src/renderSystem/RenderSystem.h"

namespace Fierce {
	VulkanGraphicsContext::VulkanGraphicsContext(VK_Device* device){
		m_activeColor = new Color3f(1.0f,1.0f,1.0f);

		m_fonts = new VK_Manager<Font*>();

		m_device = device;

		m_renderBatches.push_back(new RenderBatch(device));
		m_activeRenderBatch = m_renderBatches[0];
	}

	VulkanGraphicsContext::~VulkanGraphicsContext(){
		delete m_activeRenderBatch;

		for (RenderBatchFont* renderBatch : m_renderBatchesFont) {
			delete renderBatch;
		}

		delete m_fonts;

		delete m_activeColor;
	}

	void VulkanGraphicsContext::reset(){
		if (m_activeRenderBatch!=nullptr) {
			m_activeRenderBatch->reset();
		}
		for (RenderBatchFont* renderBatch : m_renderBatchesFont) {
			renderBatch->reset();
		}
	}

	void VulkanGraphicsContext::setColor(float r, float g, float b){
		m_activeColor->setR(r);
		m_activeColor->setG(g);
		m_activeColor->setB(b);
	}

	void VulkanGraphicsContext::setColor(int r, int g, int b){
		m_activeColor->setR((float)r / 255.0f);
		m_activeColor->setG((float)g / 255.0f);
		m_activeColor->setB((float)b / 255.0f);
	}

	void VulkanGraphicsContext::setFont(std::string fontName,int size){
		Font* font = nullptr;

		//Look for existing render batch
		for (RenderBatchFont* renderBatch:m_renderBatchesFont) {
			font = m_fonts->get(fontName);
			if (renderBatch->getFont()==font&&renderBatch->getFontSize()==size) {
				m_activeRenderBatchFont = renderBatch;
				return;
			}
		}

		//Create new render batch
		font = m_fonts->get(fontName);
		RenderBatchFont* renderBatch = new RenderBatchFont(m_device, font, size);
		m_renderBatchesFont.push_back(renderBatch);
		m_activeRenderBatchFont = renderBatch;
	}

	void VulkanGraphicsContext::drawRect(int x, int y, int width, int height){
		m_activeRenderBatch->putRectangleIndices();

		m_activeRenderBatch->putVertex(x,y);
		m_activeRenderBatch->putVertex(m_activeColor->getR(),m_activeColor->getG(),m_activeColor->getB());
		m_activeRenderBatch->putVertex(x, y+height);
		m_activeRenderBatch->putVertex(m_activeColor->getR(), m_activeColor->getG(), m_activeColor->getB());
		m_activeRenderBatch->putVertex(x+width, y+height);
		m_activeRenderBatch->putVertex(m_activeColor->getR(), m_activeColor->getG(), m_activeColor->getB());
		m_activeRenderBatch->putVertex(x+width, y);
		m_activeRenderBatch->putVertex(m_activeColor->getR(), m_activeColor->getG(), m_activeColor->getB());
	}

	void VulkanGraphicsContext::drawText(int x, int y, std::string text){
		char letter;
		Font::Char character;
		Font* font = m_activeRenderBatchFont->getFont();
		int padding = font->info.padding[0];
		float cursor = 0.0f;
		int kerning = 0;
		float sizeFactor = (float)m_activeRenderBatchFont->getFontSize() / (float) font->info.size;

		for (int i = 0; i < text.size(); i++) {
			letter = text[i];
			character = font->chars.chars[letter];

			//Search for kerning
			if (i<text.size()-1) {
				for (int j = 0; j < font->kernings.count; j++) {
					Font::Kerning kern = font->kernings.kernings[j];
					if (kern.first == text[i]&& kern.second == text[i+1]) {
						kerning = kern.amount;
					}
				}
			}

			//Texture coordinates
			float u1 = (float)character.x / (float)font->common.scaleW;
			float u2 = (float)(character.x + character.width) / (float)font->common.scaleW;
			float v1 = (float)character.y / (float)font->common.scaleH;
			float v2 = (float)(character.y + character.height) / (float)font->common.scaleH;

			//Positions
			float x1 = cursor + x + (character.xoffset * sizeFactor);
			float x2 = x1 + (character.width)* sizeFactor;
			float y1 = y - (float)(font->common.lineHeight-font->info.size)/2.0f*sizeFactor+(character.yoffset)* sizeFactor;
			//float y1 = y + (font->common.base- character.height -character.yoffset) * sizeFactor;
			float y2 = y1 + character.height * sizeFactor;
			cursor += (character.xadvance-2* font->info.padding[0]-font->info.spacing[0]) * sizeFactor+ kerning * sizeFactor;

			//Put Indices
			m_activeRenderBatchFont->putRectangleIndices();

			//Put vertices
			m_activeRenderBatchFont->putVertex(x1, y1, u1, v1);
			m_activeRenderBatchFont->putVertex(m_activeColor->getR(),m_activeColor->getG(),m_activeColor->getB());
			m_activeRenderBatchFont->putVertex(x1, y2, u1, v2);
			m_activeRenderBatchFont->putVertex(m_activeColor->getR(), m_activeColor->getG(), m_activeColor->getB());
			m_activeRenderBatchFont->putVertex(x2, y2, u2, v2);
			m_activeRenderBatchFont->putVertex(m_activeColor->getR(), m_activeColor->getG(), m_activeColor->getB());
			m_activeRenderBatchFont->putVertex(x2, y1, u2, v1);
			m_activeRenderBatchFont->putVertex(m_activeColor->getR(), m_activeColor->getG(), m_activeColor->getB());

			kerning = 0;
		}
	}

	Font* VulkanGraphicsContext::getFont(std::string fontName){
		return m_fonts->get(fontName);
	}

	void VulkanGraphicsContext::addFont(std::string name,Font* font){
		m_fonts->add(name, font);
	}
}