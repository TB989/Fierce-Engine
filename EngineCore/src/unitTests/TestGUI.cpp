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

		m_label = new GUILabel("Test Labeling");
		m_label->setX(10);
		m_label->setY(1000);

		m_button = new GUIButton("Testing Button");
		m_button->setX(200);
		m_button->setY(1000);
		m_button->setFont("Mistral");
		m_button->setForegroundColor(0, 0, 1.0f);
	}

	void TestGUI::update(double delta) {

	}

	void TestGUI::render() {
		
	}

	void TestGUI::renderGUI(GraphicsContext* context) {
		m_renderSystem->resetGraphicsContext();

		//######################################Candara##################################
		context->setColor(188, 47, 86);
		context->drawRect(10, 10, 700, 10);

		context->setFont("Candara", 10);
		context->setColor(100, 20, 255);
		context->drawText(10, 10, "Testing 123456789!");

		context->setColor(90, 47, 95);
		context->drawRect(10, 30, 700, 66);

		context->setFont("Candara", 66);
		context->setColor(255, 100, 35);
		context->drawText(10, 30, "Testing 123456789!");//30->10

		context->setColor(10, 47, 86);
		context->drawRect(10, 150, 700, 100);

		context->setFont("Candara",100);
		context->setColor(255, 255, 255);
		context->drawText(10, 150, "Testing 123456789!");
		//###############################################################################

		//######################################Jokerman#################################
		context->setColor(188, 47, 86);
		context->drawRect(810, 10, 700, 10);

		context->setFont("Jokerman", 10);
		context->setColor(255, 255, 255);
		context->drawText(810, 10, "Testing 123456789!");//10->4

		context->setColor(90, 47, 95);
		context->drawRect(810, 30, 700, 50);

		context->setFont("Jokerman", 50);
		context->setColor(255, 255, 255);
		context->drawText(810, 30, "Testing 123456789!");//30->20

		context->setColor(10, 47, 86);
		context->drawRect(810, 150, 700, 100);

		context->setFont("Jokerman", 100);
		context->setColor(255, 255, 255);
		context->drawText(810, 150, "Testing 123456789!");//150->40
		//##############################################################################

		//######################################Mistral#################################
		context->setColor(188, 47, 86);
		context->drawRect(10, 310, 700, 10);

		context->setFont("Mistral", 10);
		context->setColor(255, 255, 255);
		context->drawText(10, 310, "Testing 123456789!");

		context->setColor(90, 47, 95);
		context->drawRect(10, 330, 700, 68);

		context->setFont("Mistral", 68);
		context->setColor(255, 255, 255);
		context->drawText(10, 330, "Testing 123456789!");//330

		context->setColor(10, 47, 86);
		context->drawRect(10, 450, 700, 100);

		context->setFont("Mistral", 100);
		context->setColor(255, 255, 255);
		context->drawText(10, 450, "Testing 123456789!");//450
		//##############################################################################

		//######################################Times New Roman#########################
		context->setColor(188, 47, 86);
		context->drawRect(810, 310, 700, 10);

		context->setFont("TimesNewRoman", 10);
		context->setColor(255, 255, 255);
		context->drawText(810, 310, "Testing 123456789!");

		context->setColor(90, 47, 95);
		context->drawRect(810, 330, 700, 62);

		context->setFont("TimesNewRoman", 62);
		context->setColor(255, 255, 255);
		context->drawText(810, 330, "Testing 123456789!");//330

		context->setColor(10, 47, 86);
		context->drawRect(810, 450, 700, 100);

		context->setFont("TimesNewRoman", 100);
		context->setColor(255, 255, 255);
		context->drawText(810, 450, "Testing 123456789!");//450
		//##############################################################################

		//######################################GUI Test################################
		m_label->draw(context);
		m_button->draw(context);
		//##############################################################################

		m_renderSystem->drawGraphicsContext();
	}

	void TestGUI::cleanUp() {
		delete m_perspectiveProjectionMatrix;
		delete m_orthographicProjectionMatrix;
		delete m_action;
	}
}