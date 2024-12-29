#include "EngineCore.h"

#include "src/io/Parser.h"

#include "src/LoggingSystem.h"
#include "src/InputSystem.h"
#include "src/WindowSystem.h"

namespace Fierce {

	bool EngineCore::m_running = false;

	EngineCore::EngineCore(){
		std::map<std::string, std::string> settings = Parser::parsePropertiesFile("Engine.ini");
		if (!settings.empty()) {
			m_settings.parse(settings);
		}
	}

	EngineCore::~EngineCore(){
		
	}

	void EngineCore::run(){
		coreInit();
		init();
		m_renderSystem->postInit();

		m_running = true;
		m_window->show();
		while (m_running) {
			m_windowSystem->updateSystem();
			m_renderSystem->updateSystem();

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
		m_loggingSystem = new LoggingSystem("C:/Users/tmbal/Desktop/Fierce-Engine/logs/");
		m_loggingSystem->initSystem();
		m_logger = m_loggingSystem->createLogger("CORE", true, "ALL_LOGS");

		m_inputSystem = new InputSystem(m_loggingSystem);
		m_inputSystem->initSystem();

		m_windowSystem = new WindowSystem(m_loggingSystem,m_inputSystem);
		m_windowSystem->initSystem();
		m_window = m_windowSystem->createWindow("Fierce Engine", m_settings.windowMode, m_settings.width, m_settings.height);

		m_renderSystem = new RenderSystem(m_loggingSystem);
		m_renderSystem->setWindowHandle(m_window->getHandle());
		m_renderSystem->initSystem();
	}

	void EngineCore::coreUpdate(){}

	void EngineCore::coreRender(){}

	void EngineCore::coreCleanUp(){
		m_renderSystem->cleanUpSystem();
		delete m_renderSystem;

		m_windowSystem->deleteWindow(m_window);
		m_windowSystem->cleanUpSystem();
		delete m_windowSystem;

		m_inputSystem->cleanUpSystem();
		delete m_inputSystem;

		m_loggingSystem->deleteLogger(m_logger);
		m_loggingSystem->cleanUpSystem();
		delete m_loggingSystem;
	}

}