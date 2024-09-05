#include "EngineCore.h"
#include "io/Parser.h"

namespace Fierce {

	bool EngineCore::m_running = false;

	EngineCore::EngineCore(){
		Logger::init("C:/Users/tmbal/Desktop/Fierce-Engine/logs/");
		m_logger = new Logger("CORE",true,"ALL_LOGS");
		m_logger->info("Loading engine settings.");
		std::map<std::string, std::string> settings = Parser::parsePropertiesFile("Engine.ini");
		if (settings.empty()) {
			m_logger->warn("Failed to load engine settings, using default.");
		}
		else {
			m_settings.parse(settings);
		}
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
		m_window= m_windowSystem->createWindow("Fierce Engine", m_settings.windowMode, m_settings.width, m_settings.height);
	}

	void EngineCore::coreUpdate(){}

	void EngineCore::coreRender(){}

	void EngineCore::coreCleanUp(){
		m_windowSystem->deleteWindow(m_window);
		delete m_windowSystem;
	}

}