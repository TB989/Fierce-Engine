#include "unitTests/UnitTests.h"

using namespace Fierce;

int main() {
	TestWindow* app = new TestWindow();
	app->run();
	delete app;

	return 0;
}