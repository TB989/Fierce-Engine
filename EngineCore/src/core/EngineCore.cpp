#include "EngineCore.h"

#include "src/include/Plattform.h"

#include "src/Win32/Win32_Window.h"

#include "src/GraphicsContext.h"

namespace Fierce {

	bool EngineCore::m_running = false;

	EngineCore::EngineCore(){
		corePreInit();
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

	void EngineCore::corePreInit(){
		m_plattform = new Plattform();

		m_fileSystem = m_plattform->createFileSystem();
		m_fileSystem->initSystem("");

		//Load engine settings
		m_settingsReader = m_fileSystem->createTextFileReader("");
		m_settingsParser = new Parser_Ini(m_settingsReader);
		m_settingsParser->parseFile("Engine.ini",m_settings);
		delete m_settingsParser;
		m_fileSystem->deleteTextFileReader(m_settingsReader);
	}

	void EngineCore::coreInit(){
		m_timeDateSystem = m_plattform->createTimeDateSystem();
		m_timeDateSystem->initSystem("");
		m_timer = m_timeDateSystem->createTimer();

		m_loggingSystem = m_plattform->createLoggingSystem(m_timeDateSystem, m_fileSystem);
		m_loggingSystem->initSystem(m_settings.assetPath);
		m_logger = m_loggingSystem->createLogger("CORE", true, "ALL_LOGS");

		m_inputSystem = m_plattform->createInputSystem(m_loggingSystem);
		m_inputSystem->initSystem(m_settings.assetPath);

		m_windowSystem = m_plattform->createWindowSystem(m_loggingSystem,m_inputSystem);
		m_windowSystem->initSystem(m_settings.assetPath);
		m_window = m_windowSystem->createWindow("Fierce Engine", m_settings.windowMode, m_settings.width, m_settings.height);

		m_renderSystem = new RenderSystem(m_loggingSystem,m_fileSystem);
		m_renderSystem->setWindowHandle(((Win32_Window*)(m_window))->getHandle());
		m_renderSystem->initSystem(m_settings.assetPath);
		m_graphicsContext = m_renderSystem->getGraphicsContext();

		m_renderSystem->loadAllFonts("fonts/");
	}

	void EngineCore::coreUpdate(){
		m_timeDateSystem->updateSystem();
		m_loggingSystem->updateSystem();
		m_inputSystem->updateSystem();
		m_fileSystem->updateSystem();
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

		m_fileSystem->cleanUpSystem();
		delete m_fileSystem;

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