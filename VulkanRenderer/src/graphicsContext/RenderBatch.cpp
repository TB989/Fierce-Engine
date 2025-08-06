#include "RenderBatch.h"

#include "src/renderSystem/RenderSystem.h"

namespace Fierce {
	RenderBatch::RenderBatch(VK_Device* device){
		m_vertexBuffer = new VK_Buffer(device, VERTEX_BUFFER_SIZE * sizeof(float), VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
		m_vertexBuffer->setKeepMapped(true);
		m_vertexBuffer->create();
		m_indexBuffer = new VK_Buffer(device, INDEX_BUFFER_SIZE * sizeof(uint16_t), VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
		m_indexBuffer->setKeepMapped(true);
		m_indexBuffer->create();
		m_vertices = (float*)m_vertexBuffer->getMappedMemoryRegion();
		m_indices = (uint16_t*)m_indexBuffer->getMappedMemoryRegion();
	}

	RenderBatch::~RenderBatch(){
		delete m_vertexBuffer;
		delete m_indexBuffer;
	}

	void RenderBatch::reset() {
		m_vertexPointer = 0;
		m_indexPointer = 0;
		m_numRectangles = 0;
	}

	void RenderBatch::putIndex(uint16_t index) {
		m_indices[m_indexPointer] = index;
		m_indexPointer++;
	}

	void RenderBatch::putRectangleIndices(){
		putIndex(4 * m_numRectangles); putIndex(4 * m_numRectangles + 1); putIndex(4 * m_numRectangles + 2);
		putIndex(4 * m_numRectangles); putIndex(4 * m_numRectangles + 2); putIndex(4 * m_numRectangles + 3);
		m_numRectangles++;
	}

	void RenderBatch::putVertex(float vertex) {
		m_vertices[m_vertexPointer] = vertex;
		m_vertexPointer++;
	}

	void RenderBatch::putVertex(float v1, float v2){
		putVertex(v1);
		putVertex(v2);
	}

	void RenderBatch::putVertex(float v1, float v2, float v3){
		putVertex(v1);
		putVertex(v2);
		putVertex(v3);
	}

	void RenderBatch::putVertex(float v1, float v2, float v3, float v4){
		putVertex(v1);
		putVertex(v2);
		putVertex(v3);
		putVertex(v4);
	}
}