#pragma once

#include "vulkan/vulkan.h"

#include "src/PlatformLayer/utils/FierceStrings.h"

namespace Fierce {
	class I_DebugTools {
	public:
		virtual ~I_DebugTools() {};

		virtual void create(VkInstance instance)=0;
		virtual VkDebugUtilsMessengerCreateInfoEXT getDebugInfo() = 0;

	public:
		virtual void cmdBeginLabel(VkCommandBuffer commandBuffer,const char* label,float r,float g,float b) = 0;
		virtual void cmdEndLabel(VkCommandBuffer commandBuffer) = 0;
		virtual void cmdInsertLabel(VkCommandBuffer commandBuffer, const char* label, float r, float g, float b) = 0;

		virtual void queueBeginLabel(VkQueue queue, const char* label, float r, float g, float b) = 0;
		virtual void queueEndLabel(VkQueue queue) = 0;
		virtual void queueInsertLabel(VkQueue queue, const char* label, float r, float g, float b) = 0;

		virtual void setName(VkDevice device,VkObjectType objectType,uint64_t object,const char* name)=0;
	};

	class VK_DebugTools_debug:public I_DebugTools {
	public:
		VK_DebugTools_debug();
		~VK_DebugTools_debug() override;

		void create(VkInstance instance) override;
		VkDebugUtilsMessengerCreateInfoEXT getDebugInfo() { return m_debugCreateInfo; };

	public:
		void cmdBeginLabel(VkCommandBuffer commandBuffer, const char* label, float r, float g, float b) override;
		void cmdEndLabel(VkCommandBuffer commandBuffer) override;
		void cmdInsertLabel(VkCommandBuffer commandBuffer, const char* label, float r, float g, float b) override;

		void queueBeginLabel(VkQueue queue, const char* label, float r, float g, float b) override;
		void queueEndLabel(VkQueue queue) override;
		void queueInsertLabel(VkQueue queue, const char* label, float r, float g, float b) override;

		void setName(VkDevice device, VkObjectType objectType, uint64_t object, const char* name) override;

	private:
		template <typename T>
		T createFunctionPointer(VkInstance instance,std::string functionName) {
			T func = (T)vkGetInstanceProcAddr(instance, functionName.c_str());

			if (func == nullptr) {
				RenderSystem::LOGGER->error("Failed to load function pointer for %s.", functionName.c_str());
				return nullptr;
			}
			return func;
		}

	private:
		//Create info
		VkDebugUtilsMessengerCreateInfoEXT m_debugCreateInfo = {};
		VkDebugUtilsLabelEXT m_labelInfo = {};
		VkDebugUtilsObjectNameInfoEXT m_nameInfo = {};

		//Vulkan objects
		VkInstance m_instance = VK_NULL_HANDLE;
		VkDebugUtilsMessengerEXT m_debugMessenger = VK_NULL_HANDLE;

		//Message callback
		static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);

		//Function pointers
		PFN_vkCreateDebugUtilsMessengerEXT vkCreateDebugUtilsMessengerEXT = nullptr;
		PFN_vkDestroyDebugUtilsMessengerEXT vkDestroyDebugUtilsMessengerEXT=nullptr;

		PFN_vkCmdBeginDebugUtilsLabelEXT vkCmdBeginDebugUtilsLabelEXT=nullptr;
		PFN_vkCmdEndDebugUtilsLabelEXT vkCmdEndDebugUtilsLabelEXT = nullptr;
		PFN_vkCmdInsertDebugUtilsLabelEXT vkCmdInsertDebugUtilsLabelEXT = nullptr;

		PFN_vkQueueBeginDebugUtilsLabelEXT vkQueueBeginDebugUtilsLabelEXT = nullptr;
		PFN_vkQueueEndDebugUtilsLabelEXT vkQueueEndDebugUtilsLabelEXT = nullptr;
		PFN_vkQueueInsertDebugUtilsLabelEXT vkQueueInsertDebugUtilsLabelEXT = nullptr;
			
		PFN_vkSetDebugUtilsObjectNameEXT vkSetDebugUtilsObjectNameEXT = nullptr;
	};

	class VK_DebugTools_dummy:public I_DebugTools {
	public:
		VK_DebugTools_dummy() {};
		~VK_DebugTools_dummy() override{};

		void create(VkInstance instance) override {};
		VkDebugUtilsMessengerCreateInfoEXT getDebugInfo() override { return m_debugCreateInfo; };

	public:
		void cmdBeginLabel(VkCommandBuffer commandBuffer, const char* label, float r, float g, float b) override {};
		void cmdEndLabel(VkCommandBuffer commandBuffer) override {};
		void cmdInsertLabel(VkCommandBuffer commandBuffer, const char* label, float r, float g, float b) override {};

		void queueBeginLabel(VkQueue queue, const char* label, float r, float g, float b) override {};
		void queueEndLabel(VkQueue queue) override {};
		void queueInsertLabel(VkQueue queue, const char* label, float r, float g, float b) override {};

		void setName(VkDevice device, VkObjectType objectType, uint64_t object, const char* name) override {};

	private:
		//Create info
		VkDebugUtilsMessengerCreateInfoEXT m_debugCreateInfo = {};
	};
}//end namespace