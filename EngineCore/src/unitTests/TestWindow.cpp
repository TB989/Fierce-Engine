#include "UnitTests.h"

namespace Fierce {

	TestWindow::TestWindow() {
		//m_settings.windowMode = Window::WINDOW_MODE::FULLSCREEN;
	}

	TestWindow::~TestWindow() {

	}

	void TestWindow::init() {
		m_instance = new VK_Instance();
		m_instance->create();
	}

	void TestWindow::update() {

	}

	void TestWindow::render() {

	}

	void TestWindow::cleanUp() {
		delete m_instance;
	}

}//end namespace