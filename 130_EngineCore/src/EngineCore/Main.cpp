#include "unitTests/UnitTests.h"

using namespace Fierce;

int main() {
	TestGUI* app = new TestGUI();
	//TestGame* app = new TestGame();
	app->run();
	delete app;

	return 0;
}