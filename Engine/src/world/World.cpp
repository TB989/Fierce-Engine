#include "World.h"

#include "MathLibrary.h"
#include "GeometryLibrary.h"
#include "RendererBase.h"
#include "src/camera/Camera.h"

World::World() {
	ecs = new ECS();
	ecs->registerComponent<GeometrySettings>(0);
	ecs->registerComponent<MeshSettings>(1);
	ecs->registerComponent<Color3f>(2);
	ecs->registerComponent<Transform2D>(3);
	ecs->registerComponent<Transform3D>(4);
	ecs->registerComponent<Camera>(5);

	loader = new GeometryLoaderSystem();
	ecs->registerSystem<GeometryLoaderSystem>(loader);
	ecs->systemAddComponent<GeometryLoaderSystem, GeometrySettings>();
	ecs->systemAddComponent<GeometryLoaderSystem, MeshSettings>();
}

World::~World() {
	ecs->unregisterSystem<GeometryLoaderSystem>();

	ecs->unregisterComponent<GeometrySettings>();
	ecs->unregisterComponent<MeshSettings>();
	ecs->unregisterComponent<Color3f>();
	ecs->unregisterComponent<Transform2D>();
	ecs->unregisterComponent<Transform3D>();
	ecs->unregisterComponent<Camera>();
	delete ecs;
}