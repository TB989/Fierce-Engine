#pragma once

#include "src/VulkanRenderer/vulkanObjects/VK_Buffer.h"

namespace Fierce {

	class RenderBatch {
	public:
		RenderBatch(VK_Device* device);
		virtual ~RenderBatch();

		void reset();

		VK_Buffer* getVertexBuffer() { return m_vertexBuffer; }
		VK_Buffer* getIndexBuffer() { return m_indexBuffer; }
		int getNumIndices() { return m_indexPointer; }

		void putIndex(uint16_t index);
		void putRectangleIndices();
		void putVertex(float v1);
		void putVertex(float v1, float v2);
		void putVertex(float v1, float v2, float v3);
		void putVertex(float v1, float v2, float v3,float v4);

	private:
		int m_numRectangles = 0;

		const int VERTEX_BUFFER_SIZE = 10000;
		VK_Buffer* m_vertexBuffer = nullptr;
		float* m_vertices = nullptr;
		int m_vertexPointer = 0;

		const int INDEX_BUFFER_SIZE = 10000;
		VK_Buffer* m_indexBuffer = nullptr;
		uint16_t* m_indices = nullptr;
		int m_indexPointer = 0;
	};

}