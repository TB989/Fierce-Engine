#pragma once

#include "src/include/InputSystem.h"

#ifdef WIN32
	#include "src/Win32/Win32_TimeDateSystem.h"
	#include "src/Win32/Win32_FileSystem.h"
	#include "src/Win32/Win32_LoggingSystem.h"
	#include "src/Win32/Win32_WindowSystem.h"
#endif // WIN32

namespace Fierce {

	class Plattform {
	public:
		inline TimeDateSystem* createTimeDateSystem() { 
#ifdef WIN32
			return new Win32_TimeDateSystem();
#else
			return nullptr;
#endif // WIN32 
		}

		inline FileSystem* createFileSystem() { 
#ifdef WIN32
			return new Win32_FileSystem(); 
#else
			return nullptr;
#endif // WIN32 
		}

		inline LoggingSystem* createLoggingSystem(TimeDateSystem* timeDateSystem,FileSystem* fileSystem) { 
#ifdef WIN32
			return new Win32_LoggingSystem(timeDateSystem,fileSystem); 
#else
			return nullptr;
#endif // WIN32 
		}

		inline InputSystem* createInputSystem(LoggingSystem* loggingSystem) { 
#ifdef WIN32
			return new InputSystem(loggingSystem);
#else
			return nullptr:
#endif // WIN32 
		}

		inline WindowSystem* createWindowSystem(LoggingSystem* loggingSystem,InputSystem* inputSystem) {
#ifdef WIN32
			return new Win32_WindowSystem(loggingSystem,inputSystem); 
#else
			return nullptr;
#endif // WIN32 
		}
	};
}