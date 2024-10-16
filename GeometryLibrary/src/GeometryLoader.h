#pragma once

#include <map>
#include <vector>

#include "Geometry.h"

namespace Fierce {
	class GeometryLoader {
	public:
		void loadGeometry(GeometryType type, int numPoints, float angle, float innerRadius, int numRings, std::vector<float>& vertices, std::vector<unsigned int>& indices);
		void registerGeometry(GeometryType type, Geometry* geometry);
		void unregisterGeometry(GeometryType type);
	private:
		std::map<GeometryType, Geometry*> geometries;
	};
}//end namespace