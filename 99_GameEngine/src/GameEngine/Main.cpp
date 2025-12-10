#include "src/GameEngine/GameEngine.h"

using namespace Fierce;

int main() {
	GameEngine* engine = new GameEngine();
	engine->run();
	delete engine;
	return 0;
}