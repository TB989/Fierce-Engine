#include <Windows.h>

#include "src/core/FierceExceptions.h"
#include "src/core/Core.h"

#include "src/unitTests/UnitTests.h"

int main() {

	Test_EngineConfig* app;

	try {
		app=new Test_EngineConfig();
		app->run();
		delete app;
	}
	catch (const Fierce_Exception& e) {
		LOGGER->error(e.what());
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}