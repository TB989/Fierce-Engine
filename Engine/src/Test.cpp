#include <iostream>

#include<windows.h>

#include "DLLTest.h"

#include "Logger.h"

#include <time.h>

PFNTESTFUNCPROC testFunc;

int main() {

    Logger* logger = new Logger("Test");
    logger->info("Hello World!");
    delete logger;

    bool useVulkan = true;

    HINSTANCE instance=NULL;

    if (useVulkan) {
        instance = LoadLibrary(TEXT("../bin/VulkanRenderer.dll"));
    }
    else {
        instance = LoadLibrary(TEXT("../bin/OpenGLRenderer.dll"));
    }

    if (instance == NULL) {
        std::cout << "Unable to load renderer!";
        return 0;
    }
    else {
        testFunc = (PFNTESTFUNCPROC)GetProcAddress(instance, "testFunc");

        if (!testFunc) {
            std::cout << "Unable to load function!";
            return 0;
        }

        testFunc();

        FreeLibrary(instance);
    }

    return 0;
}