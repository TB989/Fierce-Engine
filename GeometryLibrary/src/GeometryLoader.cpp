#include "GeometryLoader.h"

void GeometryLoader::loadGeometry(GeometrySettings geometry, bool loadTextureCoordinates, bool loadNormals, std::vector<float> &vertices, std::vector<unsigned int> &indices){
	Geometry* geom = geometries[geometry.type];

	geom->getVertices(vertices,loadTextureCoordinates,loadNormals,geometry.numPoints,geometry.angle,geometry.innerRadius,geometry.numRings);
	geom->getIndices(indices, loadTextureCoordinates, loadNormals, geometry.numPoints, geometry.angle,geometry.innerRadius, geometry.numRings);
}

void GeometryLoader::registerGeometry(GeometryType type, Geometry* geometry){
	geometries[type] = geometry;
}

void GeometryLoader::unregisterGeometry(GeometryType type){
	Geometry* geometry = geometries[type];
	geometries.erase(type);
	delete geometry;
}