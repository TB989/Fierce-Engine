#include <Windows.h>
#include <exception>

#include "unitTests/UnitTests.h"

int main() {

	try {
		Test_EngineConfig* app=new Test_EngineConfig();
		app->run();
		delete app;
	}
	catch (...) {
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}