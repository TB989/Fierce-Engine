#include "RenderSystem.h"

#include "vulkanObjects/VK_Instance.h"
#include "vulkanObjects/VK_Surface.h"
#include "vulkanObjects/VK_Device.h"
#include "vulkanObjects/VK_Swapchain.h"
#include "vulkanObjects/VK_Renderpass.h"
#include "vulkanObjects/VK_Shader.h"
#include "vulkanObjects/VK_Pipeline.h"

namespace Fierce {

	Logger* RenderSystem::LOGGER = nullptr;

	RenderSystem::RenderSystem(LoggingSystem* loggingSystem){
		m_loggingSystem = loggingSystem;
	}

	RenderSystem::~RenderSystem(){}

	void RenderSystem::setWindowHandle(HWND windowHandle){
		m_windowHandle = windowHandle;
	}

	void RenderSystem::initSystem(){
		LOGGER = m_loggingSystem->createLogger("VK",true,"VULKAN");

		m_instance = new VK_Instance();
		m_instance->addCheck(new VK_Check_Device_Extensions(true, { VK_KHR_SURFACE_EXTENSION_NAME, "VK_KHR_win32_surface" }));
		m_instance->addCheck(new VK_Check_Device_Extensions(false, { VK_EXT_DEBUG_UTILS_EXTENSION_NAME }));
		m_instance->addCheck(new VK_Check_Device_ValidationLayers(false, { "VK_LAYER_KHRONOS_validation" }));
		m_instance->create();
		//m_instance->printActiveExtensions();
		//m_instance->printActiveValidationLayers();

		m_surface = new VK_Surface(m_instance->getId(), m_windowHandle);
		m_surface->create();

		m_device = new VK_Device(m_instance->getId(), m_surface->getId());
		m_device->addCheck(new VK_Check_Device_Extensions(true, { VK_KHR_SWAPCHAIN_EXTENSION_NAME }));
		m_device->addCheck(new VK_Check_Device_ValidationLayers(false, { "VK_LAYER_KHRONOS_validation" }));
		m_device->addCheck(new VK_Check_Device_General());
		m_device->addCheck(new VK_Check_Device_Queues());
		m_device->addCheck(new VK_Check_Device_Surface_Format({ VK_FORMAT_B8G8R8A8_SRGB }));
		m_device->addCheck(new VK_Check_Device_Surface_PresentMode({ VK_PRESENT_MODE_MAILBOX_KHR, VK_PRESENT_MODE_FIFO_KHR }));
		m_device->create();
		//m_device->printActiveData(true,true,true,true,true,true,true,true);

		m_swapchain = new VK_Swapchain(m_device, m_surface->getId());
		m_swapchain->create();

		m_renderpass = new VK_Renderpass(m_device);
		m_renderpass->create();

		m_vertexShader = new VK_Shader(m_device->getDevice());
		m_vertexShader->setSourceCode("firstShader_vert.spv");
		m_vertexShader->create();
		m_fragmentShader = new VK_Shader(m_device->getDevice());
		m_fragmentShader->setSourceCode("firstShader_frag.spv");
		m_fragmentShader->create();

		m_pipeline = new VK_Pipeline(m_device,m_renderpass->getId());
		m_pipeline->addVertexShader(m_vertexShader->getId());
		m_pipeline->addFragmentShader(m_fragmentShader->getId());
		m_pipeline->create();
	}

	void RenderSystem::updateSystem(){

	}

	void RenderSystem::cleanUpSystem(){
		delete m_pipeline;
		delete m_fragmentShader;
		delete m_vertexShader;
		delete m_renderpass;
		delete m_swapchain;
		delete m_device;
		delete m_surface;
		delete m_instance;
		m_loggingSystem->deleteLogger(LOGGER);
	}

}//end namespace