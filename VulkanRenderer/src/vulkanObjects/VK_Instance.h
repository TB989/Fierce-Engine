#pragma once

#include "Common.h"
#include "VulkanObject.h"

#include "VK_Helper_Extensions_ValidationLayers.h"
#include "VK_Check_System.h"

class VK_Instance:public VulkanObject,public VK_Check_System{
public:
	VK_Instance();
	~VK_Instance();

public:
	void create();
	VkInstance getId() {return instance;}

private:
	PFN_vkCreateDebugUtilsMessengerEXT loadCreateFunctionPointer(VkInstance instance);
	PFN_vkDestroyDebugUtilsMessengerEXT loadDestroyFunctionPointer(VkInstance instance);
	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);

private:
	VkInstance instance;

	ExtensionValidationLayerData extensionLayerData;

	bool isDebugSupported=false;
	PFN_vkCreateDebugUtilsMessengerEXT vkCreateDebugUtilsMessengerEXT;
	PFN_vkDestroyDebugUtilsMessengerEXT vkDestroyDebugUtilsMessengerEXT;
	VkDebugUtilsMessengerEXT debugMessenger;

private:
	uint32_t API_VERSION= VK_MAKE_VERSION(1,0,0);
	std::string APP_NAME = "FIERCE-APP";
	uint32_t APP_VERSION= VK_MAKE_VERSION(1, 0, 0);
	std::string ENGINE_NAME = "FIERCE-ENGINE";
	uint32_t ENGINE_VERSION = VK_MAKE_VERSION(1, 0, 0);
};