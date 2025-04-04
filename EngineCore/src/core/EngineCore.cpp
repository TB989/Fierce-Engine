#include "EngineCore.h"

#include "src/io/Parser.h"

#include "src/Win32/Win32_TimeDateSystem.h"
#include "src/Win32/Win32_LoggingSystem.h"
#include "src/include/InputSystem.h"
#include "src/Win32/Win32_WindowSystem.h"
#include "src/Win32/Win32_Window.h"

#include "src/GraphicsContext.h"

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
		m_timer->start();
		while (m_running) {
			coreUpdate();
			update(m_timer->getElapsedTime());
			m_renderSystem->startFrame();
			coreRender();
			render();
			renderGUI(m_graphicsContext);
			m_renderSystem->endFrame();
		}
		m_timer->stop();

		cleanUp();
		coreCleanUp();
	}

	void EngineCore::stop(){
		m_running = false;
	}

	void EngineCore::coreInit(){
		m_timeDateSystem = new Win32_TimeDateSystem();
		m_timeDateSystem->initSystem();
		m_timer = m_timeDateSystem->createTimer();

		m_loggingSystem = new Win32_LoggingSystem(m_timeDateSystem);
		m_loggingSystem->setLogDirectory(m_assetDirectory+"logs");
		m_loggingSystem->initSystem();
		m_logger = m_loggingSystem->createLogger("CORE", true, "ALL_LOGS");

		m_inputSystem = new InputSystem(m_loggingSystem);
		m_inputSystem->initSystem();

		m_windowSystem = new Win32_WindowSystem(m_loggingSystem,m_inputSystem);
		m_windowSystem->initSystem();
		m_window = m_windowSystem->createWindow("Fierce Engine", m_settings.windowMode, m_settings.width, m_settings.height);

		m_renderSystem = new RenderSystem(m_loggingSystem);
		m_renderSystem->setWindowHandle(((Win32_Window*)(m_window))->getHandle());
		m_renderSystem->initSystem();
		m_graphicsContext = m_renderSystem->getGraphicsContext();
	}

	void EngineCore::coreUpdate(){
		m_timeDateSystem->updateSystem();
		m_loggingSystem->updateSystem();
		m_inputSystem->updateSystem();
		m_windowSystem->updateSystem();
		m_renderSystem->updateSystem();
	}

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

		m_timeDateSystem->deleteTimer(m_timer);
		m_timeDateSystem->cleanUpSystem();
		delete m_timeDateSystem;
	}

}