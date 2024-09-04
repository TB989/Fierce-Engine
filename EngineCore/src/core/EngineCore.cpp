#include "EngineCore.h"

#include "src/Logger.h"

namespace Fierce {

	bool EngineCore::m_running = false;

	EngineCore::EngineCore(){
		Logger::init("C:/Users/tmbal/Desktop/Fierce-Engine/logs/");
	}

	EngineCore::~EngineCore(){
		Logger::cleanUp();
	}

	void EngineCore::run(){
		coreInit();
		init();

		m_running = true;
		m_window->show();
		while (m_running) {
			m_window->pollEvents();
			coreUpdate();
			update();
			coreRender();
			render();
		}

		cleanUp();
		coreCleanUp();
	}

	void EngineCore::stop(){
		m_running = false;
	}

	void EngineCore::coreInit(){
		m_windowSystem = new WindowSystem();
		m_windowSystem->setWindowCloseFunction(stop);
		m_window= m_windowSystem->createWindow("Fierce Engine", Window::WINDOW_MODE::WINDOWED, 800, 600);
	}

	void EngineCore::coreUpdate(){}

	void EngineCore::coreRender(){}

	void EngineCore::coreCleanUp(){
		m_windowSystem->deleteWindow(m_window);
		delete m_windowSystem;
	}

}