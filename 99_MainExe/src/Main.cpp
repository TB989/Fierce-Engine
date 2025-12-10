#include <Windows.h>
#include <iostream>
#include "Application.h"
#include "src/Layer.h"

using namespace Fierce;

using CreateGameLayerFunc = Layer*(*)();

int main() {
    Application* app=new Application();

    HMODULE gameDLL = LoadLibraryA("C:/Users/tmbal/Desktop/Fierce-Engine/bin/99_Game.dll");
    if (!gameDLL) {
        std::cerr << "Failed to load Game.dll\n";
        return -1;
    }

    auto createFunc = (CreateGameLayerFunc)GetProcAddress(gameDLL, "CreateGameLayer");
    if (!createFunc) {
        std::cerr << "Failed to find CreateGameLayer\n";
        FreeLibrary(gameDLL);
        return -1;
    }

    auto gameLayer = createFunc();
    app->PushLayer(gameLayer);
    app->Run();

    FreeLibrary(gameDLL);

    delete app;

    return 0;
}