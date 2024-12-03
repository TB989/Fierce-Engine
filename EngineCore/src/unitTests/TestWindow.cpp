#include "UnitTests.h"

#include "src/Matrix.h"

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
	}

	void TestWindow::update() {
		
	}

	void TestWindow::render() {
		
	}

	void TestWindow::cleanUp() {
		
	}

}//end namespace