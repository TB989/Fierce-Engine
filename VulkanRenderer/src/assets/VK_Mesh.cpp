#include "VK_Mesh.h"

#include "vulkanObjects/VK_Device.h"
#include "vulkanObjects/VK_Buffer.h"

namespace Fierce {

	VK_Mesh::VK_Mesh(VK_Device* device, int numVertices,int numIndices){
		m_device = device;

		m_vertexBuffer = new VK_Buffer(device, numVertices * sizeof(float), VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
		m_vertexBuffer->create();

		m_indexBuffer = new VK_Buffer(device, numIndices * sizeof(uint16_t), VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
		m_indexBuffer->create();
	}

	VK_Mesh::~VK_Mesh(){
		delete m_vertexBuffer;
		delete m_indexBuffer;
	}

	void VK_Mesh::loadVertices(int numVertices,float* vertices){
		m_numVertices += numVertices;
		m_vertexBuffer->loadData(numVertices * sizeof(float), vertices);
	}

	void VK_Mesh::loadIndices(int numIndices, uint16_t* indices){
		m_numIndices += numIndices;
		m_indexBuffer->loadData(numIndices * sizeof(uint16_t), indices);
	}

	void VK_Mesh::swapBuffers(VK_Buffer*& vertexBuffer, VK_Buffer*& indexBuffer){
		VK_Buffer* tempVertexBuffer = m_vertexBuffer;
		VK_Buffer* tempIndexBuffer = m_indexBuffer;

		m_vertexBuffer =vertexBuffer;
		m_indexBuffer = indexBuffer;
		vertexBuffer = tempVertexBuffer;
		indexBuffer = tempIndexBuffer;
	}

}//end namespace