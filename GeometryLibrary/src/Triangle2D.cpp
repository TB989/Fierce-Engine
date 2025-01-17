#include "Geometry.h"

namespace Fierce {
	void Triangle2D::getVertices(std::vector<float>& vertices, int numPoints, float angle, float innerRadius, int numRings) {
		addVertex2D(vertices, 0, 0);
		addVertex2D(vertices, 0.5f, 1);
		addVertex2D(vertices, 1, 0);
	}

	void Triangle2D::getIndices(std::vector<uint16_t>& indices, int numPoints, float angle, float innerRadius, int numRings) {
		addTriangleIndices(indices, 0, 1, 2, false);
	}
}//end namespace