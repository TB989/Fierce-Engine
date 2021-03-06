#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/
#include "01_core/Core.h"
#include "02_system/02_event/Event.h"

/* SystemIncludes*/

/* Forward declarations: 
*  -Pointers:  Pointer* myPointer;
*              Reference& myReference;
*  -Functions: Object MyFunction(Object myObject);
*              Pointer* MyFunction(Pointer* myPointer);
*              Reference& MyFunction(Reference& myReference);
*/

class Test_logging : public Core {

public:
	Test_logging();
	void onAppInit(AppInitEvent* event);
};

class Test_engineConfig : public Core {
public:
	Test_engineConfig();
	void onAppInit(AppInitEvent* event);
private:
	EngineSettings m_settings = {};
};

class Test_eventSystem : public Core {
public:
	Test_eventSystem();
	void onAppInit(AppInitEvent* event);
	void onAppUpdate(AppUpdateEvent* event);
	void onAppRender(AppRenderEvent* event);
	void onAppCleanUp(AppCleanUpEvent* event);
};

class Test_math : public Core {
public:
	Test_math();
	void onAppInit(AppInitEvent* event);
};

class Test_ECS : public Core {
public:
	Test_ECS();
	void onAppInit(AppInitEvent* event);
};

class EntityManager;
class ComponentManager;

class Test_openGLContext : public Core {
public:
	Test_openGLContext();
	void onAppInit(AppInitEvent* event);
	void onAppCleanUp(AppCleanUpEvent* event);

	void onWindowResize(WindowResizeEvent* event);

	void onKeyPressed(KeyDownEvent* event);

private:
	void removeComponents2D(int entity);
	void removeComponents3D(int entity);

private:
	EntityManager* ent;
	ComponentManager* comp;

	int rectangle;
	int triangle;
	int circle;
	int circleRing;
	
	int plane;
	int cube;
	int cylinder;
	int hollowCylinder;
	int cone;
	int sphere;
};

/**class VK_Instance;
class VK_Device;
class VK_Presentation;
class VK_Renderpass;
class VK_Pipeline;
class VK_Framebuffers;
class VK_Semaphore;
class VK_Fence;

class Test_vulkan : public Core {
public:
	Test_vulkan();
	void onAppInit(AppInitEvent* event);
	void onAppRender(AppRenderEvent* event);
	void onAppCleanUp(AppCleanUpEvent* event);
private:
	size_t currentFrame = 0;
	const int MAX_FRAMES_IN_FLIGHT = 2;

	VK_Instance* instance;
	VK_Device* device;
	VK_Presentation* presentation;
	VK_Renderpass* renderpass;
	VK_Pipeline* pipeline;
	VK_Framebuffers* framebuffers;

	std::vector<VK_Semaphore*> imageAvailableSemaphores;
	std::vector<VK_Semaphore*> renderFinishedSemaphores;
	std::vector<VK_Fence*> inFlightFences;
	std::vector<VK_Fence*> imagesInFlight;
};*/