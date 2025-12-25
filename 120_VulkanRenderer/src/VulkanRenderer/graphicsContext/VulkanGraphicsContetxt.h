#pragma once

#include "src/GUI/GraphicsContext.h"

#include "src/utils/Font.h"

#include "src/VulkanRenderer/manager/VK_Manager.h"

#include <vector>

#include "RenderBatch.h"
#include "RenderBatchFont.h"

namespace Fierce {

	class Color3f;
	class VK_Device;

	class VulkanGraphicsContext : public GraphicsContext {
	public:
		VulkanGraphicsContext(VK_Device* device);
		~VulkanGraphicsContext();

		void reset();

		void setColor(float r, float g, float b) override;
		void setColor(int r, int g, int b) override;
		void setFont(std::string font, int size) override;

		void drawRect(int x, int y, int width, int height) override;
		void drawText(int x, int y, std::string text) override;

		Font* getFont(std::string fontName) override;

		VK_Buffer* getVertexBuffer() { return m_activeRenderBatch->getVertexBuffer(); }
		VK_Buffer* getIndexBuffer() { return m_activeRenderBatch->getIndexBuffer(); }
		int getNumIndices() { return m_activeRenderBatch->getNumIndices(); }

		int getNumRenderBatchesFont() { return m_renderBatchesFont.size(); }
		RenderBatchFont* getRenderBatchFont(int index) { return m_renderBatchesFont[index]; }

		void addFont(std::string name,Font* font);

	private:
		VK_Device* m_device = nullptr;

		//Font library
		VK_Manager<Font*>* m_fonts = nullptr;

		//Active color, font
		Color3f* m_activeColor = nullptr;

		std::vector<RenderBatch*> m_renderBatches;
		RenderBatch* m_activeRenderBatch=nullptr;

		std::vector<RenderBatchFont*> m_renderBatchesFont;
		RenderBatchFont* m_activeRenderBatchFont = nullptr;
	};
};