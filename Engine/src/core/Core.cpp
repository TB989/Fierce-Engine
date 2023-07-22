#include "Core.h"

#include "src/io/Parser.h"

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
	delete eventSystem;
	delete inputSystem;
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
	//InputSystem
	inputSystem = new InputSystem();

	//Start event system
	eventSystem = new EventSystem();
	eventSystem->addListener(this, &Core::onWindowClosed);
	eventSystem->addListener(this, &Core::onKeyDown);

	//Load Window
	windowSystem = new WindowSystem(inputSystem);
	windowSystem->createWindow(m_settings.windowMode,m_settings.width,m_settings.height);
	windowSystem->createDummyWindow(m_settings.windowMode, m_settings.width, m_settings.height);
	window = windowSystem->getWindow();
	window->registerForRawInput();
	dummyWindow = windowSystem->getDummyWindow();

	//Load renderer
	loadRenderer();
	renderer_init(dummyWindow->getHandle(), window->getHandle());

	init();

	window->show();
}

void Core::coreUpdate() {
	update();
}

void Core::coreRender() {
	renderer_startFrame();
	doRender(); 
	renderer_endFrame();
}

void Core::coreCleanUp() {
	renderer_cleanUp();
	//delete windowSystem;
	//delete eventSystem;
	cleanUp();
}


void Core::onWindowClosed(WindowCloseEvent* event) {
	stop();
}

void Core::onKeyDown(KeyDownEvent* event) {
	if (event->m_key == VK_ESCAPE) {
		stop();
	}
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