#include "Core.h"

#include "Logger.h"
#include "io/Parser.h"

Logger* Core::LOGGER = new Logger("CORE");

Core::Core() {
	Core::LOGGER->info("Loading engine settings.");
	std::map<std::string, std::string> settings = Parser::parsePropertiesFile("Engine.ini");
	if (settings.empty()) {
		Core::LOGGER->warn("Failed to load engine settings, using default.");
	}
	else {
		m_settings.parse(settings);
	}
}

Core::~Core() {
	FreeLibrary(m_renderer);

	delete windowSystem;
}

void Core::run() {
	coreInit();

	//Setup game loop
	if (m_settings.windowMode != HEADLESS) {
		window->show();
		LOGGER->info("Starting game loop.");
		running = true;
	}

	//Start game loop
	while (running) {
		window->pollEvents();
		coreUpdate();
		coreRender();
	}

	coreCleanUp();
}

void Core::coreInit() {
	//Load Window
	windowSystem = new WindowSystem(&m_settings,this);
	dummyWindow = windowSystem->getDummyWindow();
	window = windowSystem->getWindow();

	//Load renderer
	loadRenderer();
	initRenderer(dummyWindow->getHandle(), window->getHandle());

	init();

	window->show();
}

void Core::coreUpdate() {
	update();
}

void Core::coreRender() {
	render();
}

void Core::coreCleanUp() {
	cleanUpRenderer();
	cleanUp();
}

void Core::loadRenderer(){
	//Choose rendering API and open DLL
	switch (m_settings.api) {
	case API::OPEN_GL:
		Core::LOGGER->info("Loading rendering library OpenGL.");
		m_renderer = LoadLibrary(TEXT("../bin/OpenGLRenderer.dll"));
		break;
	case API::VULKAN:
		Core::LOGGER->info("Loading rendering library Vulkan.");
		m_renderer = LoadLibrary(TEXT("../bin/VulkanRenderer.dll"));
		break;
	default:
		Core::LOGGER->warn("Rendering library is not supported, loading OpenGL.");
		m_renderer = LoadLibrary(TEXT("../bin/OpenGLRenderer.dll"));
		break;
	}

	//Load functions
	if (m_renderer == NULL) {
		Core::LOGGER->error("Unable to load renderer!");
	}
	else {
		initRenderer = (PFN_INIT_RENDERER_PROC)GetProcAddress(m_renderer, "initRenderer");

		if (!initRenderer) {
			Core::LOGGER->error("Unable to load function!");
		}

		cleanUpRenderer = (PFN_CLEAN_UP_RENDERER_PROC)GetProcAddress(m_renderer, "cleanUpRenderer");

		if (!cleanUpRenderer) {
			Core::LOGGER->error("Unable to load function!");
		}
	}
}