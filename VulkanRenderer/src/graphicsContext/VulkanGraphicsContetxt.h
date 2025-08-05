#pragma once

#include "src/GraphicsContext.h"

#include "src/vulkanObjects/VK_Buffer.h"

#include "src/utils/Font.h"

#include "src/manager/VK_Manager.h"

namespace Fierce {

	class Color3f;
	class VK_Device;

	class VulkanGraphicsContext : public GraphicsContext {
	public:
		VulkanGraphicsContext(VK_Device* device);
		~VulkanGraphicsContext();

		void reset();

		void setColor(int r, int g, int b) override;
		void setFont(std::string font, int size) override;

		void drawRect(int x, int y, int width, int height) override;
		void drawText(int x, int y, std::string text) override;

		VK_Buffer* getVertexBuffer() { return m_vertexBuffer; }
		VK_Buffer* getIndexBuffer() { return m_indexBuffer; }
		int getNumIndices() { return m_indexPointer; }

		VK_Buffer* getVertexBufferFont() { return m_vertexBufferFont; }
		VK_Buffer* getIndexBufferFont() { return m_indexBufferFont; }
		int getNumIndicesFont() { return m_indexPointerFont; }
		int getActiveFontTextureId() { return m_activeFont->page.textureId; };

		void addFont(std::string name,Font* font);

	private:
		void putIndex(uint16_t index);
		void putVertex(float vertex);

		void putFontIndex(uint16_t index);
		void putFontVertex(float vertex);

	private:
		VK_Device* m_device = nullptr;

		//Font library
		VK_Manager<Font*>* m_fonts = nullptr;

		//Active color, font
		Color3f* m_activeColor = nullptr;
		Font* m_activeFont=nullptr;
		int m_activeFontSize = 0;

		//Buffers for colored rectangles
		int m_numRectangles = 0;

		const int VERTEX_BUFFER_SIZE = 10000;
		VK_Buffer* m_vertexBuffer = nullptr;
		float* m_vertices = nullptr;
		int m_vertexPointer = 0;

		const int INDEX_BUFFER_SIZE = 10000;
		VK_Buffer* m_indexBuffer = nullptr;
		uint16_t* m_indices = nullptr;
		int m_indexPointer = 0;

		//Buffers for text
		int m_numFontRectangles = 0;

		const int VERTEX_BUFFER_SIZE_FONT = 10000;
		VK_Buffer* m_vertexBufferFont = nullptr;
		float* m_verticesFont = nullptr;
		int m_vertexPointerFont = 0;

		const int INDEX_BUFFER_SIZE_FONT = 10000;
		VK_Buffer* m_indexBufferFont = nullptr;
		uint16_t* m_indicesFont = nullptr;
		int m_indexPointerFont = 0;
	};
};