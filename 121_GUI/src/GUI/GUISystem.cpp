#include "GUISystem.h"

#include "GUIHelper.h"

namespace Fierce {

	Fierce::GUISystem::GUISystem(){

	}

	GUISystem::~GUISystem(){

	}

	void GUISystem::initSystem(std::string assetDirectory){
		if (m_loggingSystem != nullptr) {
			m_logger = m_loggingSystem->createLogger("GUI", true, "ALL_LOGS");
			m_logger->info("Init GUI system");
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
	}

	void GUISystem::updateSystem(){

	}

	void GUISystem::cleanUpSystem(){
		if (m_logger != nullptr) {
			m_logger->info("Clean up GUI system");
			m_loggingSystem->deleteLogger(m_logger);
		}
	}
}