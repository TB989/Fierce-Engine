#include "UnitTests.h"

#include "src/Transform.h"
#include "src/Matrix.h"
#include "src/Vector.h"

#define STB_IMAGE_IMPLEMENTATION
#include "src/io/stb_image.h"

namespace Fierce {

	TestWindow::TestWindow() {
		//m_settings.windowMode = Window::WINDOW_MODE::FULLSCREEN;
	}

	TestWindow::~TestWindow() {

	}

	void TestWindow::init() {
		//###################################### MESHES ###############################################################################
		float vertices[] = {
			-0.5f, -0.5f, 1.0f, 0.0f, 0.0f,1.0f,0.0f,
			0.5f, -0.5f, 0.0f, 1.0f, 0.0f,0.0f,0.0f,
			0.5f, 0.5f, 0.0f, 0.0f, 1.0f,0.0f,1.0f,
			-0.5f, 0.5f, 1.0f, 1.0f, 1.0f,1.0f,1.0f
		};

		uint16_t indices[] = {
			0, 2,1, 2, 0,3
		};

		m_meshId=m_renderSystem->newMesh(4*7,6);
		m_renderSystem->meshLoadVertices(m_meshId,4*7,vertices);
		m_renderSystem->meshLoadIndices(m_meshId, 6, indices);

		//################################################ TEXTURES #####################################################################
		int texWidth, texHeight, texChannels;
		stbi_uc* pixels = stbi_load("C:/Users/tmbal/Desktop/Fierce-Engine/VulkanRenderer/res/texture.jpg", &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
		if (!pixels) {
			m_logger->error("Unable to load image.");
		}
		m_textureId = m_renderSystem->newTexture(texWidth,texHeight,4);
		m_renderSystem->textureLoadData(m_textureId, pixels);
		stbi_image_free(pixels);

		//################################################ Matrices ######################################################################
		transform1 = new Transform2D(100.0f,0.0f,100.0f,100.0f,0.0f);
		transform2 = new Transform2D(-100.0f, 0.0f, 100.0f, 100.0f, 0.0f);

		m_modelMatrix1 = new Mat4();
		m_modelMatrix2 = new Mat4();

		m_viewMatrix = new Mat4();
		m_projectionMatrix = new Mat4(); 
		m_projectionMatrix->setToOrthographicProjection(false, 800.0f,600.0f, 0.0f, 1.0f);

		m_renderSystem->setOrthographicProjection(m_projectionMatrix->get());
	}

	void TestWindow::update() {
		float angle1 = transform1->getRotation();
		transform1->setRotation(angle1+0.01f);

		float angle2 = transform2->getRotation();
		transform2->setRotation(angle2 + 0.01f);
	}

	void TestWindow::render() {
		m_renderSystem->startFrame();
		//Quad1
		m_modelMatrix1->setToTransform(transform1);
		m_renderSystem->loadModelMatrix(m_modelMatrix1->get());
		m_renderSystem->drawMesh(m_meshId);
		//Quad2
		m_modelMatrix2->setToTransform(transform2);
		m_renderSystem->loadModelMatrix(m_modelMatrix2->get());
		m_renderSystem->drawMesh(m_meshId);
		//
		m_renderSystem->endFrame();
	}

	void TestWindow::cleanUp() {
		delete transform1;
		delete transform2;
		delete m_modelMatrix1;
		delete m_modelMatrix2;
		delete m_viewMatrix;
		delete m_projectionMatrix;
	}

}//end namespace