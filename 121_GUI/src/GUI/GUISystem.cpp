#include "GUISystem.h"

#include "GUIHelper.h"

namespace Fierce {

	Logger* GUISystem::LOGGER = nullptr;

	Fierce::GUISystem::GUISystem(){

	}

	GUISystem::~GUISystem(){

	}

	void GUISystem::initSystem(std::string assetDirectory){
		if (m_loggingSystem != nullptr) {
			LOGGER = m_loggingSystem->createLogger("GUI", true, "ALL_LOGS");
			LOGGER->info("Init GUI system");
		}

		m_graphicsContext = m_renderSystem->getGraphicsContext();
		GUIHelper::linkGraphicsContext(m_graphicsContext);
	}

	void GUISystem::linkSystem(System* system){
		if (dynamic_cast<LoggingSystem*>(system)) {
			m_loggingSystem = (LoggingSystem*)system;
		}
		if (dynamic_cast<RenderSystem*>(system)) {
			m_renderSystem = (RenderSystem*)system;
		}
		if (dynamic_cast<InputSystem*>(system)) {
			m_inputSystem = (InputSystem*)system;
		}
	}

	void GUISystem::updateSystem(){

	}

	void GUISystem::cleanUpSystem(){
		if (LOGGER != nullptr) {
			LOGGER->info("Clean up GUI system");
			m_loggingSystem->deleteLogger(LOGGER);
		}
	}
}