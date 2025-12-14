#pragma once

#include "src/PlatformLayer/include/InputSystem.h"

#include "src/systems/ITimeDateSystem.h"

#ifdef _WIN32
	#include "src/PlatformLayer/Win32/Win32_TimeDateSystem.h"
	#include "src/PlatformLayer/Win32/Win32_FileSystem.h"
	#include "src/PlatformLayer/Win32/Win32_LoggingSystem.h"
	#include "src/PlatformLayer/Win32/Win32_WindowSystem.h"
#endif // WIN32

namespace Fierce {

	class Plattform {
	public:
		inline ITimeDateSystem* createTimeDateSystem() { 
#ifdef _WIN32
			return new Win32_TimeDateSystem();
#else
			return nullptr;
#endif // WIN32 
		}

		inline FileSystem* createFileSystem() { 
#ifdef _WIN32
			return new Win32_FileSystem(); 
#else
			return nullptr;
#endif // WIN32 
		}

		inline LoggingSystem* createLoggingSystem() { 
#ifdef _WIN32
			return new Win32_LoggingSystem(); 
#else
			return nullptr;
#endif // WIN32 
		}

		inline InputSystem* createInputSystem() { 
#ifdef _WIN32
			return new InputSystem();
#else
			return nullptr;
#endif // WIN32 
		}

		inline WindowSystem* createWindowSystem() {
#ifdef _WIN32
			return new Win32_WindowSystem(); 
#else
			return nullptr;
#endif // WIN32 
		}
	};
}