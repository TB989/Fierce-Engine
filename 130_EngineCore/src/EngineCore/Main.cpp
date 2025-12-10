#include "unitTests/UnitTests.h"

using namespace Fierce;

int main() {
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//TestGUI* app = new TestGUI();
	TestGame* app = new TestGame();
	app->run();
	delete app;

	return 0;
}