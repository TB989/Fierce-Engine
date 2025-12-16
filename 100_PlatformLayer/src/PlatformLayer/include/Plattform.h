#pragma once

#include "src/systems/ITimeDateSystem.h"
#include "src/systems/IFileSystem.h"
#include "src/systems/ILoggingSystem.h"
#include "src/systems/IInputSystem.h"
#include "src/systems/IWindowSystem.h"

#ifdef _WIN32
	#include "src/PlatformLayer/Win32/Win32_TimeDateSystem.h"
	#include "src/PlatformLayer/Win32/Win32_FileSystem.h"
	#include "src/PlatformLayer/Win32/Win32_LoggingSystem.h"
	#include "src/PlatformLayer/InputSystem/InputSystem.h"
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

		inline void deleteTimeDateSystem(ITimeDateSystem* system) {
#ifdef _WIN32
			delete system;
#else
			return;
#endif // WIN32 
		}

		inline IFileSystem* createFileSystem() { 
#ifdef _WIN32
			return new Win32_FileSystem(); 
#else
			return nullptr;
#endif // WIN32 
		}

		inline void deleteFileSystem(IFileSystem* system) {
#ifdef _WIN32
			delete system;
#else
			return;
#endif // WIN32 
		}

		inline ILoggingSystem* createLoggingSystem() { 
#ifdef _WIN32
			return new Win32_LoggingSystem(); 
#else
			return nullptr;
#endif // WIN32 
		}

		inline void deleteLoggingSystem(ILoggingSystem* system) {
#ifdef _WIN32
			delete system;
#else
			return;
#endif // WIN32 
		}

		inline IInputSystem* createInputSystem() { 
#ifdef _WIN32
			return new InputSystem();
#else
			return nullptr;
#endif // WIN32 
		}

		inline void deleteInputSystem(IInputSystem* system) {
#ifdef _WIN32
			delete system;
#else
			return;
#endif // WIN32 
		}

		inline IWindowSystem* createWindowSystem() {
#ifdef _WIN32
			return new Win32_WindowSystem(); 
#else
			return nullptr;
#endif // WIN32 
		}

		inline void deleteWindowSystem(IWindowSystem* system) {
#ifdef _WIN32
			delete system;
#else
			return;
#endif // WIN32 
		}
	};
}