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
	
}

void Core::run() {
	coreInit();

	//while (running) {
		coreUpdate();
		coreRender();
	//}
	coreCleanUp();
}

void Core::coreInit() {
	init();
}

void Core::coreUpdate() {
	update();
}

void Core::coreRender() {
	render();
}

void Core::coreCleanUp() {
	cleanUp();
}