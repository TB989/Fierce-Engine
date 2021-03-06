#include "UnitTests.h"

#include "02_system/01_logging/Logger.h"
#include "02_system/02_event/EventSystem.h"

Test_logging::Test_logging() {
	eventSystem->addListener(this, &Test_logging::onAppInit);
}

void Test_logging::onAppInit(AppInitEvent* event) {
	Loggers::CORE->error("ERROR %i", 102);
	Loggers::CORE->warn("WARN %1.5f", 85.255496464);
	Loggers::CORE->info("INFO %s", "String");
}