#include "Geometry.h"

void Cylinder3D::getVertices(std::vector<float>& vertices, bool loadTextureCoordinates, bool loadNormals, int numPoints, float angle, float innerRadius, int numRings) {
	if (loadTextureCoordinates&&loadNormals) {
		//Back
		addVertex3D(vertices, 0.0f, 0.0f, -0.5f); addTextureCoordinate(vertices, 0.5f, 0.5f); addNormal(vertices,NEG_Z,0.0f,0.0f);
		addCircleVertices3D(vertices, loadTextureCoordinates,-0.5f, numPoints, 0.5f, angle, NEG_Z,0.0f);
		//Front
		addVertex3D(vertices, 0.0f, 0.0f, 0.5f); addTextureCoordinate(vertices, 0.5f, 0.5f); addNormal(vertices, POS_Z, 0.0f, 0.0f);
		addCircleVertices3D(vertices, loadTextureCoordinates, 0.5f, numPoints, 0.5f, angle, POS_Z,0.0f);
		//Outside
		addCircleVertices3D(vertices, loadTextureCoordinates, -0.5f, numPoints, 0.5f, angle, CIRCLE_X_Y,0.0f);
		addCircleVertices3D(vertices, loadTextureCoordinates, 0.5f, numPoints, 0.5f, angle, CIRCLE_X_Y,0.0f);
		//Fills
		if (angle!=360.0f) {
			addQuadVertices3D(vertices,loadTextureCoordinates,loadNormals,-0.5f,0.5f,numPoints,0.0f,0.0f,false);
			addQuadVertices3D(vertices, loadTextureCoordinates, loadNormals,-0.5f, 0.5f, numPoints, 0.0f, angle,true);
		}
	}
	else if (loadTextureCoordinates) {
		addVertex3D(vertices, 0.0f, 0.0f, -0.5f); addTextureCoordinate(vertices, 0.5f, 0.5f);
		addCircleVertices3D(vertices, loadTextureCoordinates, -0.5f, numPoints, 0.5f, angle,NONE, 0.0f);
		addVertex3D(vertices, 0.0f, 0.0f, 0.5f); addTextureCoordinate(vertices, 0.5f, 0.5f);
		addCircleVertices3D(vertices, loadTextureCoordinates, 0.5f, numPoints, 0.5f, angle,NONE,0.0f);
	}
	else if (loadNormals) {
		//Back
		addVertex3D(vertices, 0.0f, 0.0f, -0.5f); addNormal(vertices, NEG_Z, 0.0f, 0.0f);
		addCircleVertices3D(vertices, loadTextureCoordinates, -0.5f, numPoints, 0.5f, angle,NEG_Z,0.0f);
		//Front
		addVertex3D(vertices, 0.0f, 0.0f, 0.5f); addNormal(vertices, POS_Z, 0.0f, 0.0f);
		addCircleVertices3D(vertices, loadTextureCoordinates, 0.5f, numPoints, 0.5f, angle,POS_Z,0.0f);
		//Outside
		addCircleVertices3D(vertices, loadTextureCoordinates, -0.5f, numPoints, 0.5f, angle, CIRCLE_X_Y,0.0f);
		addCircleVertices3D(vertices, loadTextureCoordinates, 0.5f, numPoints, 0.5f, angle, CIRCLE_X_Y,0.0f);
		//Fills
		if (angle != 360.0f) {
			addQuadVertices3D(vertices, loadTextureCoordinates, loadNormals,-0.5f, 0.5f, numPoints, 0.0f,0.0f,false);
			addQuadVertices3D(vertices, loadTextureCoordinates, loadNormals, -0.5f, 0.5f, numPoints, 0.0f,angle,true);
		}
	}
	else {
		addVertex3D(vertices, 0.0f, 0.0f, -0.5f);
		addCircleVertices3D(vertices, loadTextureCoordinates, -0.5f, numPoints, 0.5f, angle,NONE,0.0f);
		addVertex3D(vertices, 0.0f, 0.0f, 0.5f);
	}
}

void Cylinder3D::getIndices(std::vector<unsigned int>& indices, bool loadTextureCoordinates, bool loadNormals, int numPoints, float angle, float innerRadius, int numRings) {
	if (loadNormals) {
		//Front
		addCircleIndices(indices, numPoints, angle, 0, 1, false);
		//Back
		addCircleIndices(indices, numPoints, angle, numPoints + 1, numPoints + 2, true);
		//Outside
		addCircleRingIndices(indices, numPoints, angle, 2*numPoints+2, 3*numPoints + 2, false);
	}
	else {
		addCircleIndices(indices, numPoints, angle, 0, 1, false);
		addCircleIndices(indices, numPoints, angle, numPoints + 1, numPoints + 2, true);
		addCircleRingIndices(indices, numPoints, angle, 1, numPoints + 2, false);
	}

	if (angle!=360.0f) {
		if (loadNormals) {
			addQuadIndices(indices, 4 * numPoints + 2, 4 * numPoints + 3, 4 * numPoints + 4, 4 * numPoints + 5, true);
			addQuadIndices(indices, 4 * numPoints + 6, 4 * numPoints + 9, 4 * numPoints + 8, 4 * numPoints + 7, true);
		}
		else {
			addQuadIndices(indices, 0, 1, numPoints + 2, numPoints + 1, true);
			addQuadIndices(indices, numPoints, 0, numPoints + 1, 2 * numPoints + 1, true);
		}
	}
}