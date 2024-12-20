#include "Geometry.h"

namespace Fierce {
	void CircleRing2D::getVertices(std::vector<float>& vertices, int numPoints, float angle, float innerRadius, int numRings) {
		addCircleVertices2D(vertices, 0.5f, 0.5f, numPoints, innerRadius, angle);
		addCircleVertices2D(vertices, 0.5f, 0.5f, numPoints, 0.5f, angle);
	}

	void CircleRing2D::getIndices(std::vector<uint16_t>& indices, int numPoints, float angle, float innerRadius, int numRings) {
		addCircleRingIndices(indices, numPoints, angle, 0, numPoints, false);
	}
}//end namespace