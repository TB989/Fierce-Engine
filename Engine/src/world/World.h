#pragma once

#include "src/ECS/ECS.h"
#include "src/system/geometryLoader/GeometryLoaderSystem.h"

class World {
public:
	World();
	~World();

public:
	ECS* ecs;
	GeometryLoaderSystem* loader;
};