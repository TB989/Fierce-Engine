#include "World.h"

#include "GeometryLibrary.h"
#include "RendererBase.h"
#include "MathLibrary.h"

World::World() {
	//Init ECS
	entityManager = new EntityManager(50);
	componentManager = new ComponentManager();
	componentManager->registerComponent<GeometrySettings>(50);
	componentManager->registerComponent<MeshSettings>(50);
	componentManager->registerComponent<Color3f>(1);
}

World::~World() {
	//Delete ECS
	componentManager->unregisterComponent<GeometrySettings>();
	componentManager->unregisterComponent<MeshSettings>();
	componentManager->unregisterComponent<Color3f>();
	delete componentManager;
	delete entityManager;
}