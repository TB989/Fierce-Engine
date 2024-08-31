#include "src/Logger.h"

int main() {
	Logger::init("C:/Users/tmbal/Desktop/Fierce-Engine/logs/");

	Logger* logger = new Logger("TEST",true,"Test");
	logger->info("Hallo!");
	logger->warn("Hallo! %i",6);
	logger->error("Hallo! %1.3f",5.8456f);
	logger->log("TESTING","Hallo! %1.3f %i", 5.8456f,6);

	Logger* logger2 = new Logger("TEST2", false, "AB");
	logger2->info("Hallo!");
	logger2->warn("Hallo! %i", 6);
	logger2->error("Hallo! %1.3f", 5.8456f);
	logger2->log("TESTING", "Hallo! %1.3f %i", 5.8456f, 6);

	Logger::cleanUp();
	return 0;
}