#pragma once

#include "System.h"

#include <vector>

namespace Fierce {
	enum GeometryType {
		RECTANGLE,
		CIRCLE,
		CIRCLE_RING,
		TRIANGLE,

		PLANE,
		CUBE,
		CYLINDER,
		HOLLOW_CYLINDER,
		CONE,
		SPHERE
	};

	class IGeometrySystem:public System{
	public:
		virtual void loadGeometry(GeometryType type, int numPoints, float angle, float innerRadius, int numRings, std::vector<float>& vertices, std::vector<uint16_t>& indices)=0;
	};
}