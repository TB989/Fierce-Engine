#pragma once

#include "src/VulkanRenderer/renderSystem/RenderSystem.h"
#include "src/PlatformLayer/include/LoggingSystem.h"
#include "src/PlatformLayer/utils/System.h"

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

	private:
		LoggingSystem* m_loggingSystem = nullptr;
		Logger* m_logger = nullptr;

		RenderSystem* m_renderSystem = nullptr;
		GraphicsContext* m_graphicsContext = nullptr;

		std::string m_fontDirectory;
	};

}