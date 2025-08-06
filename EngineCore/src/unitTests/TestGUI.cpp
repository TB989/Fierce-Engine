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
		m_orthographicProjectionMatrix->setToOrthographicProjection(false, m_window->getWidth(), m_window->getHeight(), 0.0f, 1.0f);
		m_renderSystem->setOrthographicProjection(m_orthographicProjectionMatrix->get());

		m_perspectiveProjectionMatrix = new Mat4();
		m_perspectiveProjectionMatrix->setToPerspectiveProjection(false, (float)m_window->getWidth() / (float)m_window->getHeight(), 60.0f, 0.1f, 1000.0f);
		m_renderSystem->setPerspectiveProjection(m_perspectiveProjectionMatrix->get());
	}

	void TestGUI::update(double delta) {

	}

	void TestGUI::render() {
		
	}

	void TestGUI::renderGUI(GraphicsContext* context) {
		m_renderSystem->resetGraphicsContext();

		context->setColor(188, 47, 86);
		context->drawRect(10, 200, 700, 30);

		context->setFont("Jokerman", 22);
		context->setColor(0, 0, 0);
		context->drawText(10, 200, "Hello World! @123456789");

		context->setColor(90, 47, 95);
		context->drawRect(10, 250, 700, 44);

		context->setFont("Candara", 44);
		context->setColor(0, 0, 0);
		context->drawText(10, 250, "Hello World! @123456789");

		context->setColor(10, 47, 86);
		context->drawRect(10, 300, 700, 66);

		context->setFont("Jokerman",66);
		context->setColor(255,255,255);
		context->drawText(10, 300, "Hello World! @123456789"); 

		m_renderSystem->drawGraphicsContext();
	}

	void TestGUI::cleanUp() {
		delete m_perspectiveProjectionMatrix;
		delete m_orthographicProjectionMatrix;
		delete m_action;
	}
}