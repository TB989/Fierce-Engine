#include "UnitTests.h"

#include "src/Transform.h"
#include "src/Matrix.h"

#include "src/Parser_Fnt.h"

#define STB_IMAGE_IMPLEMENTATION
#include "src/io/stb_image.h"

#include "src/include/InputSystem.h"

#include "src/utils/Font.h"

namespace Fierce {

	TestGUI::TestGUI() {
		//Parse font
		m_font = new Font();
		std::string fontDirectory = m_settings.assetPath;
		fontDirectory.append("fonts/");
		TextFileReader* reader = m_fileSystem->createTextFileReader(fontDirectory);
		Parser_Fnt* parser = new Parser_Fnt(reader);
		parser->parseFile("Candara.fnt", m_font);
		delete parser;
		m_fileSystem->deleteTextFileReader(reader);
	}

	TestGUI::~TestGUI() {

	}

	void TestGUI::init() {
		int texWidth, texHeight, texChannels;
		stbi_uc* pixels = stbi_load("C:/Users/tmbal/Desktop/Fierce-Engine/VulkanRenderer/res/Candara.png", &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
		if (!pixels) {
			m_logger->error("Unable to load image.");
		}
		m_textureId = m_renderSystem->newTexture(texWidth, texHeight, 4);
		m_renderSystem->textureLoadData(m_textureId, pixels);
		stbi_image_free(pixels);

		m_action = new Action_StopEngine(this);
		m_inputSystem->addAction(BINDING::KEY_ESC, m_action, true);
		m_inputSystem->addAction(BINDING::KEY_ESC, m_action, false);

		m_viewMatrix = new Mat4();
		m_viewTransform = new Transform3D();

		m_orthographicProjectionMatrix = new Mat4();
		m_orthographicProjectionMatrix->setToOrthographicProjection(false, 800.0f, 600.0f, 0.0f, 1.0f);
		m_renderSystem->setOrthographicProjection(m_orthographicProjectionMatrix->get());

		m_perspectiveProjectionMatrix = new Mat4();
		m_perspectiveProjectionMatrix->setToPerspectiveProjection(false, 800.0f / 600.0f, 60.0f, 0.1f, 1000.0f);
		m_renderSystem->setPerspectiveProjection(m_perspectiveProjectionMatrix->get());
	}

	void TestGUI::update(double delta) {

	}

	void TestGUI::render() {
		m_renderSystem->bindPipeline("Main3D");
		m_viewMatrix->setToView(m_viewTransform);
		m_renderSystem->setViewMatrix(m_viewMatrix->get());
		m_renderSystem->bindPipeline("Main");
		m_renderSystem->bindPipeline("Font");
	}

	void TestGUI::renderGUI(GraphicsContext* context) {
		m_renderSystem->bindPipeline("GUI");
		context->setColor(188, 47, 86);
		context->drawRect(200, 200, 250, 20);

		m_renderSystem->drawGraphicsContext();
	}

	void TestGUI::cleanUp() {
		delete m_viewTransform;
		delete m_perspectiveProjectionMatrix;
		delete m_orthographicProjectionMatrix;
		delete m_viewMatrix;
		delete m_action;
	}

}