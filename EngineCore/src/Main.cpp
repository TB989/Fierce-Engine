#include "unitTests/UnitTests.h"

using namespace Fierce;

int main() {
	//TestGUI* app = new TestGUI();
	TestGame* app = new TestGame();
	app->setAssetDirectory("C:/Users/tmbal/Desktop/Fierce-Engine/00_Assets/");
	app->run();
	delete app;

	return 0;
}