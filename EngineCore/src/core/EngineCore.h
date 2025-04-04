#pragma once

#include <string>

#include "EngineSettings.h"

#include "src/renderSystem/RenderSystem.h"

namespace Fierce {

	class TimeDateSystem;
	class Timer;
	class LoggingSystem;
	class Logger;
	class InputSystem;
	class WindowSystem;
	class Window;

	class GraphicsContext;

	class EngineCore {
	public:
		EngineCore();
		~EngineCore();

		void run();
		static void stop();

		void setAssetDirectory(std::string assetDirectory) { m_assetDirectory = assetDirectory; }
		std::string getAssetDirectory() { return m_assetDirectory; }

	public:
		virtual void init()=0;
		virtual void update(double delta) = 0;
		virtual void render()=0;
		virtual void renderGUI(GraphicsContext* context) = 0;
		virtual void cleanUp()=0;

	private:
		void coreInit();
		void coreUpdate();
		void coreRender();
		void coreCleanUp();

	protected:
		EngineSettings m_settings = {};

	private:
		std::string m_assetDirectory = "";
		static bool m_running;

	protected:
		TimeDateSystem* m_timeDateSystem = nullptr;
		Timer* m_timer = nullptr;

		LoggingSystem* m_loggingSystem = nullptr;
		Logger* m_logger = nullptr;

		InputSystem* m_inputSystem=nullptr;

		WindowSystem* m_windowSystem=nullptr;
		Window* m_window=nullptr;

		RenderSystem* m_renderSystem=nullptr;
		GraphicsContext* m_graphicsContext = nullptr;
	};

}//end namespace