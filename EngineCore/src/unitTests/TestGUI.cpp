#include "UnitTests.h"

#include "src/Matrix.h"

#include "src/include/InputSystem.h"

namespace Fierce {

	TestGUI::TestGUI() {

	}

	TestGUI::~TestGUI() {

	}

	void TestGUI::init() {
		m_action = new Action_StopEngine(this);
		m_inputSystem->addAction(BINDING::KEY_ESC, m_action, true);
		m_inputSystem->addAction(BINDING::KEY_ESC, m_action, false);

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
		
	}

	void TestGUI::renderGUI(GraphicsContext* context) {
		m_renderSystem->bindPipeline("GUI");
		context->setColor(188, 47, 86);
		context->drawRect(200, 200, 250, 20);

		context->setColor(90, 47, 95);
		context->drawRect(200, 250, 250, 20);

		context->setColor(10, 47, 86);
		context->drawRect(200, 300, 250, 20);

		m_renderSystem->drawGraphicsContext();
	}

	void TestGUI::cleanUp() {
		delete m_perspectiveProjectionMatrix;
		delete m_orthographicProjectionMatrix;
		delete m_action;
	}
}