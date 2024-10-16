#include "GeometryLoader.h"

namespace Fierce {
	void GeometryLoader::loadGeometry(GeometryType type, int numPoints, float angle, float innerRadius, int numRings, std::vector<float>& vertices, std::vector<unsigned int>& indices) {
		Geometry* geom = geometries[type];

		geom->getVertices(vertices, numPoints, angle, innerRadius, numRings);
		geom->getIndices(indices, numPoints, angle, innerRadius, numRings);
	}

	void GeometryLoader::registerGeometry(GeometryType type, Geometry* geometry) {
		geometries[type] = geometry;
	}

	void GeometryLoader::unregisterGeometry(GeometryType type) {
		Geometry* geometry = geometries[type];
		geometries.erase(type);
		delete geometry;
	}
}//end namespace