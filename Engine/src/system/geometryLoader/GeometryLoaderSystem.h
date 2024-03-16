#pragma once

#include "Logger.h"
#include "GeometryLibrary.h"
#include "src/ECS/System.h"

class GeometryLoaderSystem :public System{
public:
	GeometryLoaderSystem();
	~GeometryLoaderSystem();

private:
	void processArchetype(Archetype* archetype);

private:
	Logger* logger;
	GeometryLoader* geometryLoader;
};