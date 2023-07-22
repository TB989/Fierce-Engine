#include <Windows.h>

#include "src/core/Core.h"

#include "src/unitTests/UnitTests.h"

int main() {
	Test_GeometryLibrary* app;

	try {
		app=new Test_GeometryLibrary();
		app->run();
		delete app;
	}
	catch (const Fierce_Exception& e) {
		LOGGER->error(e.what());
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}