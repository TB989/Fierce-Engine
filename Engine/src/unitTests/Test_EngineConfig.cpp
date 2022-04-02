#include "UnitTests.h"

#include "Logger.h"
#include <Windows.h>
#include "DLLTest.h"
#include <iostream>

PFNTESTFUNCPROC testFunc;

Test_EngineConfig::Test_EngineConfig() {
    Logger* logger = new Logger("Test");
    logger->info("Hello World!");
    delete logger;

    bool useVulkan = true;

    HINSTANCE instance = NULL;

    if (useVulkan) {
        instance = LoadLibrary(TEXT("../bin/VulkanRenderer.dll"));
    }
    else {
        instance = LoadLibrary(TEXT("../bin/OpenGLRenderer.dll"));
    }

    if (instance == NULL) {
        std::cout << "Unable to load renderer!";
    }
    else {
        testFunc = (PFNTESTFUNCPROC)GetProcAddress(instance, "testFunc");

        if (!testFunc) {
            std::cout << "Unable to load function!";
        }
        else {
            testFunc();
        }

        FreeLibrary(instance);
    }
}

void Test_EngineConfig::init() {

}

void Test_EngineConfig::update() {

}

void Test_EngineConfig::render() {

}

void Test_EngineConfig::cleanUp() {

}