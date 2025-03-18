#pragma once

#include "src/GraphicsContext.h"

#include "src/vulkanObjects/VK_Buffer.h"

namespace Fierce {

	class Color3f;
	class VK_Device;

	class VulkanGraphicsContext : public GraphicsContext {
	public:
		VulkanGraphicsContext(VK_Device* device);
		~VulkanGraphicsContext();

		void reset();

		void setColor(int r, int g, int b) override;

		void drawRect(int x, int y, int width, int height) override;
		void drawText(int x, int y, std::string text) override;

		VK_Buffer* getVertexBuffer() { return m_vertexBuffer; }
		VK_Buffer* getIndexBuffer() { return m_indexBuffer; }
		int getNumIndices() { return m_numIndices; }

	private:
		void putIndex(uint16_t index);
		void putVertex(float vertex);

	private:
		Color3f* m_color = nullptr;

		VK_Device* m_device = nullptr;

		const int VERTEX_BUFFER_SIZE = 10000;
		VK_Buffer* m_vertexBuffer = nullptr;
		float* m_vertices = nullptr;
		int m_numVertices = 0;
		int m_vertexPointer = 0;

		const int INDEX_BUFFER_SIZE = 10000;
		VK_Buffer* m_indexBuffer = nullptr;
		uint16_t* m_indices = nullptr;
		int m_numIndices = 0;
		int m_indexPointer = 0;
	};
};