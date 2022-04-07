#include <Windows.h>

#include "core/FierceExceptions.h"
#include "core/Core.h"

#include "unitTests/UnitTests.h"

int main() {

	Test_EngineConfig* app;

	try {
		app=new Test_EngineConfig();
		app->run();
		delete app;
	}
	catch (const Fierce_Exception& e) {
		Core::LOGGER->error(e.what());
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}