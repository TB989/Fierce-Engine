#pragma once

#include "src/GUI/GraphicsContext.h"

namespace Fierce {

	class GUISystem :public System {
	public:
		GUISystem();
		~GUISystem();

		void initSystem(std::string assetDirectory) override;
		void linkSystem(System* system) override;
		void updateSystem() override;
		void cleanUpSystem() override;

		GraphicsContext* getGraphicsContext() {
			return m_graphicsContext;
		}

	public:
		static Logger* LOGGER;

	private:
		LoggingSystem* m_loggingSystem = nullptr;

		RenderSystem* m_renderSystem = nullptr;
		GraphicsContext* m_graphicsContext = nullptr;

		InputSystem* m_inputSystem = nullptr;

		std::string m_fontDirectory;
	};

}