#include "Core.h"

#include "io/Parser.h"

Core::Core() {
	LOGGER->info("Loading engine settings.");
	std::map<std::string, std::string> settings = Parser::parsePropertiesFile("Engine.ini");
	if (settings.empty()) {
		LOGGER->warn("Failed to load engine settings, using default.");
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
	loadShaders();
	loadPipelines();

	init();

	window->show();
}

void Core::coreUpdate() {
	update();
}

void Core::coreRender() {
	render();
	doRender();
}

void Core::coreCleanUp() {
	cleanUpRenderer();
	cleanUp();
}

void Core::loadRenderer(){
	//Choose rendering API and open DLL
	switch (m_settings.api) {
	case API::OPEN_GL:
		LOGGER->info("Loading rendering library OpenGL.");
		m_renderer = LoadLibrary(TEXT("../bin/OpenGLRenderer.dll"));
		break;
	case API::VULKAN:
		LOGGER->info("Loading rendering library Vulkan.");
		m_renderer = LoadLibrary(TEXT("../bin/VulkanRenderer.dll"));
		break;
	default:
		LOGGER->warn("Rendering library is not supported, loading OpenGL.");
		m_renderer = LoadLibrary(TEXT("../bin/OpenGLRenderer.dll"));
		break;
	}

	//Load render functions
	loadAllFunctions(m_renderer);
}