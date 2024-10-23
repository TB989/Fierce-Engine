#include "UnitTests.h"

#include "src/Matrix.h"

namespace Fierce {

	TestWindow::TestWindow() {
		//m_settings.windowMode = Window::WINDOW_MODE::FULLSCREEN;
	}

	TestWindow::~TestWindow() {

	}

	void TestWindow::init() {

		//Create matrices
		m_modelMatrix = new Mat4();
		m_modelMatrix->scale(100.0f, 100.0f, 1.0f);
		m_viewMatrix = new Mat4();
		m_projectionMatrix = new Mat4();
	}

	void TestWindow::update() {
		//m_modelMatrix->rotateZ(0.01f);
		//m_projectionMatrix->setToOrthographicProjection(false, (float)m_device->getSurfaceData()->swapchainWidth, (float)m_device->getSurfaceData()->swapchainHeight, 0.0f, 1.0f);

		//FrameData& frameData = framesData[currentFrame];
		//frameData.ubo->loadData(3 * 16 * sizeof(float), m_modelMatrix->get(), m_viewMatrix->get(), m_projMatrix->get());
	}

	void TestWindow::render() {
		//frameData.commandBuffer->beginRenderpass(m_renderpass->getId(), m_framebuffers->getFramebuffer(imageIndex));
		//frameData.commandBuffer->bindPipeline(m_pipeline->getId());
		//frameData.commandBuffer->bindVertexBuffer(m_vertexBuffer->getId());
		//frameData.commandBuffer->bindIndexBuffer(m_indexBuffer->getId());
		//frameData.commandBuffer->setViewport(static_cast<float>(m_device->getSurfaceData()->swapchainWidth), static_cast<float>(m_device->getSurfaceData()->swapchainHeight));
		//frameData.commandBuffer->setScissor(m_device->getSurfaceData()->swapchainWidth, m_device->getSurfaceData()->swapchainHeight);
		//frameData.commandBuffer->bindDescriptorSet(m_pipeline, frameData.descriptorSet->getId());
		//frameData.commandBuffer->renderIndexed(6);
		//frameData.commandBuffer->endRenderpass();
	}

	void TestWindow::cleanUp() {
		
	}

}//end namespace