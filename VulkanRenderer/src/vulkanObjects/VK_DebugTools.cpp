#include "VK_DebugTools.h"

#include "renderSystem/RenderSystem.h"

namespace Fierce {
	VK_DebugTools_debug::VK_DebugTools_debug(){
		m_debugCreateInfo = {};
		m_debugCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		m_debugCreateInfo.pNext = nullptr;
		m_debugCreateInfo.flags = 0;
		m_debugCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
		m_debugCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
		m_debugCreateInfo.pfnUserCallback = debugCallback;
		m_debugCreateInfo.pUserData = nullptr;

		m_labelInfo = {};
		m_labelInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT;
		m_labelInfo.pNext = nullptr;
		m_labelInfo.pLabelName = "";
		m_labelInfo.color[0] = 0.0f;
		m_labelInfo.color[1] = 0.0f;
		m_labelInfo.color[2] = 0.0f;
		m_labelInfo.color[3] = 1.0f;

		m_nameInfo = {};
		m_nameInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT;
		m_nameInfo.pNext = nullptr;
		m_nameInfo.pObjectName = "";
	}

	VK_DebugTools_debug::~VK_DebugTools_debug(){
		vkDestroyDebugUtilsMessengerEXT(m_instance, m_debugMessenger, nullptr);
	}

	void VK_DebugTools_debug::create(VkInstance instance){
		m_instance = instance;

		vkCreateDebugUtilsMessengerEXT = createFunctionPointer<PFN_vkCreateDebugUtilsMessengerEXT>(m_instance,"vkCreateDebugUtilsMessengerEXT");
		vkDestroyDebugUtilsMessengerEXT = createFunctionPointer<PFN_vkDestroyDebugUtilsMessengerEXT>(m_instance, "vkDestroyDebugUtilsMessengerEXT");

		vkCmdBeginDebugUtilsLabelEXT = createFunctionPointer<PFN_vkCmdBeginDebugUtilsLabelEXT>(m_instance, "vkCmdBeginDebugUtilsLabelEXT");
		vkCmdEndDebugUtilsLabelEXT = createFunctionPointer<PFN_vkCmdEndDebugUtilsLabelEXT>(m_instance, "vkCmdEndDebugUtilsLabelEXT");
		vkCmdInsertDebugUtilsLabelEXT = createFunctionPointer<PFN_vkCmdInsertDebugUtilsLabelEXT>(m_instance, "vkCmdInsertDebugUtilsLabelEXT");

		vkQueueBeginDebugUtilsLabelEXT = createFunctionPointer<PFN_vkQueueBeginDebugUtilsLabelEXT>(m_instance, "vkQueueBeginDebugUtilsLabelEXT");
		vkQueueEndDebugUtilsLabelEXT = createFunctionPointer<PFN_vkQueueEndDebugUtilsLabelEXT>(m_instance, "vkQueueEndDebugUtilsLabelEXT");
		vkQueueInsertDebugUtilsLabelEXT = createFunctionPointer<PFN_vkQueueInsertDebugUtilsLabelEXT>(m_instance, "vkQueueInsertDebugUtilsLabelEXT");

		vkSetDebugUtilsObjectNameEXT = createFunctionPointer<PFN_vkSetDebugUtilsObjectNameEXT>(m_instance, "vkSetDebugUtilsObjectNameEXT");

		if (vkCreateDebugUtilsMessengerEXT(m_instance, &m_debugCreateInfo, nullptr, &m_debugMessenger) != VK_SUCCESS) {
			RenderSystem::LOGGER->error("Failed to create debug messenger.");
		}
	}

	void VK_DebugTools_debug::cmdBeginLabel(VkCommandBuffer commandBuffer, const char* label, float r, float g, float b){
		m_labelInfo.pLabelName = label;
		m_labelInfo.color[0] = 1.0f;
		m_labelInfo.color[1] = 0.0f;
		m_labelInfo.color[2] = 0.0f;

		vkCmdBeginDebugUtilsLabelEXT(commandBuffer, &m_labelInfo);
	}

	void VK_DebugTools_debug::cmdEndLabel(VkCommandBuffer commandBuffer){
		vkCmdEndDebugUtilsLabelEXT(commandBuffer);
	}

	void VK_DebugTools_debug::cmdInsertLabel(VkCommandBuffer commandBuffer, const char* label, float r, float g, float b){
		m_labelInfo.pLabelName = label;
		m_labelInfo.color[0] = 1.0f;
		m_labelInfo.color[1] = 0.0f;
		m_labelInfo.color[2] = 0.0f;

		vkCmdInsertDebugUtilsLabelEXT(commandBuffer, &m_labelInfo);
	}

	void VK_DebugTools_debug::queueBeginLabel(VkQueue queue, const char* label, float r, float g, float b) {
		m_labelInfo.pLabelName = label;
		m_labelInfo.color[0] = 1.0f;
		m_labelInfo.color[1] = 0.0f;
		m_labelInfo.color[2] = 0.0f;

		vkQueueBeginDebugUtilsLabelEXT(queue, &m_labelInfo);
	}

	void VK_DebugTools_debug::queueEndLabel(VkQueue queue) {
		vkQueueEndDebugUtilsLabelEXT(queue);
	}

	void VK_DebugTools_debug::queueInsertLabel(VkQueue queue, const char* label, float r, float g, float b) {
		m_labelInfo.pLabelName = label;
		m_labelInfo.color[0] = 1.0f;
		m_labelInfo.color[1] = 0.0f;
		m_labelInfo.color[2] = 0.0f;

		vkQueueInsertDebugUtilsLabelEXT(queue, &m_labelInfo);
	}

	void VK_DebugTools_debug::setName(VkDevice device, VkObjectType objectType, uint64_t object, const char* name){
		m_nameInfo.objectType = objectType;
		m_nameInfo.objectHandle = object;
		m_nameInfo.pObjectName = name;

		vkSetDebugUtilsObjectNameEXT(device, &m_nameInfo);
	}

	VKAPI_ATTR VkBool32 VKAPI_CALL VK_DebugTools_debug::debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
		RenderSystem::LOGGER->error("%s", pCallbackData->pMessage);
		return VK_FALSE;
	}
}//end namespace