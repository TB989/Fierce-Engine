#include "Geometry.h"

void Cone3D::getVertices(std::vector<float>& vertices, bool loadTextureCoordinates, bool loadNormals,int numPoints, float angle, float innerRadius, int numRings) {
	if (loadTextureCoordinates) {
		addVertex3D(vertices, 0.0f, 0.0f, -0.5f, 0.5f, 0.5f);
	}
	else {
		addVertex3D(vertices, 0.0f, 0.0f, -0.5f);
	}
	addCircleVertices3D(vertices, loadTextureCoordinates, 0.0f, 0.0f, -0.5f, numPoints, 0.5f, angle);
	if (loadTextureCoordinates) {
		addVertex3D(vertices, 0.0f, 0.0f, 0.5f, 0.5f, 0.5f);
	}
	else {
		addVertex3D(vertices, 0.0f, 0.0f, 0.5f);
	}
}

void Cone3D::getIndices(std::vector<unsigned int>& indices, bool loadTextureCoordinates, bool loadNormals, int numPoints, float angle, float innerRadius, int numRings) {
	addCircleIndices(indices, numPoints, angle, 0, 1, false);
	addCircleIndices(indices, numPoints, angle, numPoints+1, 1, true);

	if (angle != 360.0f) {
		addTriangleIndices(indices, 0, 1, numPoints + 1, true);
		addTriangleIndices(indices, numPoints, 0, numPoints + 1, true);
	}
}