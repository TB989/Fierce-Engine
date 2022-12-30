#include "Common.h"

#include <stdexcept>
#include "vulkanObjects/VulkanObject.h"
#include <Windows.h>

class VK_Exception :public std::runtime_error {
public:
	VK_Exception(std::string message) :runtime_error(message) {}
};

inline void CHECK_VK(VkResult result, std::string message) {
	std::string errorString;
	switch (result) {
	case VK_SUCCESS:
	case VK_NOT_READY:
	case VK_TIMEOUT:
	case VK_EVENT_SET:
	case VK_EVENT_RESET:
	case VK_INCOMPLETE:
	case VK_SUBOPTIMAL_KHR:
		return;

	case VK_ERROR_OUT_OF_HOST_MEMORY:
		errorString = "VK Error: VK_ERROR_OUT_OF_HOST_MEMORY";
		break;
	case VK_ERROR_OUT_OF_DEVICE_MEMORY:
		errorString = "VK Error: VK_ERROR_OUT_OF_DEVICE_MEMORY";
		break;
	case VK_ERROR_INITIALIZATION_FAILED:
		errorString = "VK Error: VK_ERROR_INITIALIZATION_FAILED";
		break;
	case VK_ERROR_MEMORY_MAP_FAILED:
		errorString = "VK Error: VK_ERROR_MEMORY_MAP_FAILED";
		break;
	case VK_ERROR_DEVICE_LOST:
		errorString = "VK Error: VK_ERROR_DEVICE_LOST";
		break;
	case VK_ERROR_EXTENSION_NOT_PRESENT:
		errorString = "VK Error: VK_ERROR_EXTENSION_NOT_PRESENT";
		break;
	case VK_ERROR_FEATURE_NOT_PRESENT:
		errorString = "VK Error: VK_ERROR_FEATURE_NOT_PRESENT";
		break;
	case VK_ERROR_LAYER_NOT_PRESENT:
		errorString = "VK Error: VK_ERROR_LAYER_NOT_PRESENT";
		break;
	case VK_ERROR_INCOMPATIBLE_DRIVER:
		errorString = "VK Error: VK_ERROR_INCOMPATIBLE_DRIVER";
		break;
	case VK_ERROR_TOO_MANY_OBJECTS:
		errorString = "VK Error: VK_ERROR_TOO_MANY_OBJECTS";
		break;
	case VK_ERROR_FORMAT_NOT_SUPPORTED:
		errorString = "VK Error: VK_ERROR_FORMAT_NOT_SUPPORTED";
		break;
	case VK_ERROR_SURFACE_LOST_KHR:
		errorString = "VK Error: VK_ERROR_SURFACE_LOST_KHR";
		break;
	case VK_ERROR_OUT_OF_DATE_KHR:
		errorString = "VK Error: VK_ERROR_OUT_OF_DATE_KHR";
		break;
	case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
		errorString = "VK Error: VK_ERROR_INCOMPATIBLE_DISPLAY_KHR";
		break;
	case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
		errorString = "VK Error: VK_ERROR_NATIVE_WINDOW_IN_USE_KHR";
		break;
	case VK_ERROR_VALIDATION_FAILED_EXT:
		errorString = "VK Error: VK_ERROR_VALIDATION_FAILED_EXT";
		break;
	default:
		errorString = "VK Error: VK_UNKNOWN_ERROR";
	}

	std::wstring temp1 = std::wstring(message.begin(), message.end());
	std::wstring temp2 = std::wstring(errorString.begin(), errorString.end());
	MessageBox(NULL, temp1.c_str(), temp2.c_str(), MB_ICONERROR);
	throw VK_Exception(message.c_str());
}