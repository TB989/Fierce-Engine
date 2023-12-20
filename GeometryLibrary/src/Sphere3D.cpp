#include "Geometry.h"

void Sphere3D::getVertices(std::vector<float>& vertices, bool loadTextureCoordinates, bool loadNormals, int numPoints, float angle, float innerRadius, int numRings) {
	float da = 180.0f / (numRings+1);

	if (loadTextureCoordinates && loadNormals) {
		addVertex3D(vertices, 0.0f, 0.0f, -0.5f); addTextureCoordinate(vertices, 0.5f, 0.5f); addNormal(vertices, NEG_Z, 0.0f, 0.0f);
		for (int i = 0; i < numRings; i++) {
			float radius = 0.5f * sin(M_PI / 180.0f * (i + 1) * da);
			float height = -0.5f * cos(M_PI / 180.0f * (i + 1) * da);
			addCircleVertices3D(vertices, loadTextureCoordinates, height, numPoints, radius, 360.0f, CIRCLE_X_Y, height);
		}
		addVertex3D(vertices, 0.0f, 0.0f, 0.5f); addTextureCoordinate(vertices, 0.5f, 0.5f); addNormal(vertices, POS_Z, 0.0f, 0.0f);
	}
	else if (loadTextureCoordinates) {
		addVertex3D(vertices, 0.0f, 0.0f, -0.5f); addTextureCoordinate(vertices, 0.5f, 0.5f);
		for (int i = 0; i < numRings; i++) {
			float radius = 0.5f * sin(M_PI / 180.0f * (i + 1) * da);
			float height = -0.5f * cos(M_PI / 180.0f * (i + 1) * da);
			addCircleVertices3D(vertices, loadTextureCoordinates, height, numPoints, radius, 360.0f, NONE, 0.0f);
		}
		addVertex3D(vertices, 0.0f, 0.0f, 0.5f); addTextureCoordinate(vertices, 0.5f, 0.5f);
	}
	else if (loadNormals) {
		addVertex3D(vertices, 0.0f, 0.0f, -0.5f); addNormal(vertices, NEG_Z, 0.0f, 0.0f);
		for (int i = 0; i < numRings; i++) {
			float radius = 0.5f * sin(M_PI / 180.0f * (i + 1) * da);
			float height = -0.5f * cos(M_PI / 180.0f * (i + 1) * da);
			addCircleVertices3D(vertices, loadTextureCoordinates, height, numPoints, radius, 360.0f, CIRCLE_X_Y, height);
		}
		addVertex3D(vertices, 0.0f, 0.0f, 0.5f); addNormal(vertices, POS_Z, 0.0f, 0.0f);
	}
	else {
		addVertex3D(vertices, 0.0f, 0.0f, -0.5f);
		for (int i = 0; i < numRings; i++) {
			float radius = 0.5f * sin(M_PI / 180.0f * (i + 1) * da);
			float height = -0.5f * cos(M_PI / 180.0f * (i + 1) * da);
			addCircleVertices3D(vertices, loadTextureCoordinates, height, numPoints, radius, 360.0f, NONE, 0.0f);
		}
		addVertex3D(vertices, 0.0f, 0.0f, 0.5f);
	}
}

void Sphere3D::getIndices(std::vector<unsigned int>& indices, bool loadTextureCoordinates, bool loadNormals, int numPoints, float angle, float innerRadius, int numRings) {
	addCircleIndices(indices, numPoints, 360.0f, 0, 1, false);
	for (int i = 0; i < numRings-1; i++) {
		addCircleRingIndices(indices, numPoints, 360.0f, i * numPoints + 1, (i+1)*numPoints + 1,false);
	}
	addCircleIndices(indices, numPoints, 360.0f, numRings*numPoints + 1, (numRings-1)*numPoints+1, true);
}