#pragma once

#include "vulkan/vulkan.h"

#include "src/vulkanObjects/VK_Buffer.h"

namespace Fierce {

	class VK_Device;

	class VK_Mesh{
	public:
		VK_Mesh(VK_Device* device,int numVertices, int numIndices);
		~VK_Mesh();

		void loadVertices(int numVertices, float* vertices);
		void loadIndices(int numIndices, uint16_t* indices);

		int getNumVertices() { return m_numVertices; }
		int getNumIndices() { return m_numIndices; }

		VK_Buffer* getVertexBuffer() { return m_vertexBuffer; }
		VK_Buffer* getIndexBuffer() { return m_indexBuffer; }

		void swapBuffers(VK_Buffer*& vertexBuffer,VK_Buffer*& indexBuffer);

	private:
		VK_Device* m_device = nullptr;
		VK_Buffer* m_vertexBuffer = nullptr;
		VK_Buffer* m_indexBuffer = nullptr;

		int m_numVertices=0;
		int m_numIndices=0;
	};
}//end namespace