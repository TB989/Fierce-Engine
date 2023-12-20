#include "Geometry.h"

void Cone3D::getVertices(std::vector<float>& vertices, bool loadTextureCoordinates, bool loadNormals,int numPoints, float angle, float innerRadius, int numRings) {
	if (loadTextureCoordinates && loadNormals) {
		//Back
		addVertex3D(vertices, 0.0f, 0.0f, -0.5f); addTextureCoordinate(vertices, 0.5f, 0.5f); addNormal(vertices,NEG_Z, 0.0f, 0.0f);
		addCircleVertices3D(vertices, loadTextureCoordinates, -0.5f, numPoints, 0.5f, angle, NEG_Z, 0.0f);
		//Outside
		addVertex3D(vertices, 0.0f, 0.0f, 0.5f); addTextureCoordinate(vertices, 0.5f, 0.5f); addNormal(vertices, POS_Z, 0.0f, 0.0f);
		addCircleVertices3D(vertices, loadTextureCoordinates, -0.5f, numPoints, 0.5f, angle, CIRCLE_X_Y, 1.0f);
		//Fill
		if (angle != 360.0f) {
			addTriangleVertices3D(vertices, loadTextureCoordinates, loadNormals, -0.5f, 0.5f, numPoints, 0.0f, 0.0f, false);
			addTriangleVertices3D(vertices, loadTextureCoordinates, loadNormals, -0.5f, 0.5f, numPoints, 0.0f, angle, true);
		}
	}
	else if (loadTextureCoordinates) {
		addVertex3D(vertices, 0.0f, 0.0f, -0.5f); addTextureCoordinate(vertices, 0.5f, 0.5f);
		addCircleVertices3D(vertices, loadTextureCoordinates, -0.5f, numPoints, 0.5f, angle, NONE, 0.0f);
		addVertex3D(vertices, 0.0f, 0.0f, 0.5f); addTextureCoordinate(vertices, 0.5f, 0.5f);
	}
	else if (loadNormals) {
		//Back
		addVertex3D(vertices, 0.0f, 0.0f, -0.5f); addNormal(vertices, NEG_Z, 0.0f, 0.0f);
		addCircleVertices3D(vertices, loadTextureCoordinates, -0.5f, numPoints, 0.5f, angle, NEG_Z, 0.0f);
		//Outside
		addVertex3D(vertices, 0.0f, 0.0f, 0.5f); addNormal(vertices, POS_Z, 0.0f, 0.0f);
		addCircleVertices3D(vertices, loadTextureCoordinates, -0.5f, numPoints, 0.5f, angle, CIRCLE_X_Y, 1.0f);
		//Fill
		if (angle != 360.0f) {
			addTriangleVertices3D(vertices, loadTextureCoordinates, loadNormals, -0.5f, 0.5f, numPoints, 0.0f, 0.0f, false);
			addTriangleVertices3D(vertices, loadTextureCoordinates, loadNormals, -0.5f, 0.5f, numPoints, 0.0f, angle, true);
		}
	}
	else {
		addVertex3D(vertices, 0.0f, 0.0f, -0.5f);
		addCircleVertices3D(vertices, loadTextureCoordinates, -0.5f, numPoints, 0.5f, angle, NONE, 0.0f);
		addVertex3D(vertices, 0.0f, 0.0f, 0.5f);
	}
}

void Cone3D::getIndices(std::vector<unsigned int>& indices, bool loadTextureCoordinates, bool loadNormals, int numPoints, float angle, float innerRadius, int numRings) {
	if (loadNormals) {
		//Back
		addCircleIndices(indices, numPoints, angle, 0, 1, false);
		//Outside
		addCircleIndices(indices, numPoints, angle, numPoints + 1, numPoints+2, true);
	}
	else {
		addCircleIndices(indices, numPoints, angle, 0, 1, false);
		addCircleIndices(indices, numPoints, angle, numPoints + 1, 1, true);
	}

	if (angle != 360.0f) {
		if (loadNormals) {
			addTriangleIndices(indices, 2*numPoints+2, 2 * numPoints + 3, 2 * numPoints + 4, true);
			addTriangleIndices(indices, 2 * numPoints + 5, 2 * numPoints + 7, 2 * numPoints + 6, true);
		}
		else {
			addTriangleIndices(indices, 0, 1, numPoints + 1, true);
			addTriangleIndices(indices, numPoints, 0, numPoints + 1, true);
		}
	}
}