#pragma once

#include "Geometry.h"

#include <vector>
#include <map>

class ComponentGeometry;

class GeometryLoader{
public:
	void loadGeometry(GeometrySettings geometry,std::vector<float> &vertices,std::vector<unsigned int> &indices);
	void registerGeometry(GeometryType type, Geometry* geometry);
	void unregisterGeometry(GeometryType type);
private:
	std::map<GeometryType, Geometry*> geometries;
};