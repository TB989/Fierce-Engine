#include "Geometry.h"

void Cylinder3D::getVertices(std::vector<float>& vertices, bool loadTextureCoordinates, bool loadNormals, int numPoints, float angle, float innerRadius, int numRings) {
	if (loadTextureCoordinates) {
		addVertex3D(vertices, 0.0f, 0.0f, -0.5f, 0.0f, 0.0f);
	}
	else {
		addVertex3D(vertices, 0.0f, 0.0f, -0.5f);
	}
	addCircleVertices3D(vertices, loadTextureCoordinates, 0.0f, 0.0f, -0.5f, numPoints, 0.5f, angle);
	if (loadTextureCoordinates) {
		addVertex3D(vertices, 0.0f, 0.0f, 0.5f, 0.0f, 0.0f);
	}
	else {
		addVertex3D(vertices, 0.0f, 0.0f, 0.5f);
	}
	addCircleVertices3D(vertices, loadTextureCoordinates, 0.0f, 0.0f, 0.5f, numPoints, 0.5f, angle);
}

void Cylinder3D::getIndices(std::vector<unsigned int>& indices, int numPoints, float angle, float innerRadius, int numRings) {
	addCircleIndices(indices, numPoints, angle, 0, 1,false);
	addCircleIndices(indices, numPoints, angle, numPoints + 1, numPoints + 2, true);
	addCircleRingIndices(indices,numPoints,angle,1,numPoints+2,false);

	if (angle!=360.0f) {
		addQuadIndices(indices, 0, 1, numPoints + 2, numPoints + 1, true);
		addQuadIndices(indices, numPoints, 0, numPoints + 1, 2*numPoints + 1, true);
	}
}