#include "Geometry.h"

namespace Fierce{
	void Circle2D::getVertices(std::vector<float>& vertices, int numPoints, float angle, float innerRadius, int numRings) {
		addVertex2D(vertices, 0.5f, 0.5f);
		addCircleVertices2D(vertices, 0.5f, 0.5f, numPoints, 0.5f, angle);
	}

	void Circle2D::getIndices(std::vector<uint16_t>& indices, int numPoints, float angle, float innerRadius, int numRings) {
		addCircleIndices(indices, numPoints, angle, 0, 1, false);
	}
}//end namespace