#include "Geometry.h"

void HollowCylinder3D::getVertices(std::vector<float>& vertices, bool loadTextureCoordinates, bool loadNormals,int numPoints, float angle, float innerRadius, int numRings) {
	if (loadTextureCoordinates && loadNormals) {
		//Back
		addCircleVertices3D(vertices, loadTextureCoordinates, -0.5f, numPoints, 0.5f, angle,NEG_Z, 0.0f);
		addCircleVertices3D(vertices, loadTextureCoordinates, -0.5f, numPoints, innerRadius, angle,NEG_Z, 0.0f);
		//Front
		addCircleVertices3D(vertices, loadTextureCoordinates, 0.5f, numPoints, 0.5f, angle, POS_Z, 0.0f);
		addCircleVertices3D(vertices, loadTextureCoordinates, 0.5f, numPoints, innerRadius, angle, POS_Z, 0.0f);
		//Outside
		addCircleVertices3D(vertices, loadTextureCoordinates, -0.5f, numPoints, 0.5f, angle, CIRCLE_X_Y, 0.0f);
		addCircleVertices3D(vertices, loadTextureCoordinates, 0.5f, numPoints, 0.5f, angle, CIRCLE_X_Y, 0.0f);
		//Inside
		addCircleVertices3D(vertices, loadTextureCoordinates, -0.5f, numPoints, innerRadius, angle, CIRCLE_X_Y_INVERTED, 0.0f);
		addCircleVertices3D(vertices, loadTextureCoordinates, 0.5f, numPoints, innerRadius, angle, CIRCLE_X_Y_INVERTED, 0.0f);
		//Fills
		if (angle != 360.0f) {
			addQuadVertices3D(vertices, loadTextureCoordinates, loadNormals, -0.5f, 0.5f, numPoints, innerRadius, 0.0f, false);
			addQuadVertices3D(vertices, loadTextureCoordinates, loadNormals, -0.5f, 0.5f, numPoints, innerRadius, angle, true);
		}
	}
	else if (loadTextureCoordinates) {
		addCircleVertices3D(vertices, loadTextureCoordinates, -0.5f, numPoints, innerRadius, angle,NONE, 0.0f);
		addCircleVertices3D(vertices, loadTextureCoordinates, -0.5f, numPoints, 0.5f, angle,NONE, 0.0f);
		addCircleVertices3D(vertices, loadTextureCoordinates, 0.5f, numPoints, innerRadius, angle,NONE, 0.0f);
		addCircleVertices3D(vertices, loadTextureCoordinates, 0.5f, numPoints, 0.5f, angle,NONE, 0.0f);
	}
	else if (loadNormals) {
		//Back
		addCircleVertices3D(vertices, loadTextureCoordinates, -0.5f, numPoints, 0.5f, angle, NEG_Z, 0.0f);
		addCircleVertices3D(vertices, loadTextureCoordinates, -0.5f, numPoints, innerRadius, angle,NEG_Z, 0.0f);
		//Front
		addCircleVertices3D(vertices, loadTextureCoordinates, 0.5f, numPoints, 0.5f, angle, POS_Z, 0.0f);
		addCircleVertices3D(vertices, loadTextureCoordinates, 0.5f, numPoints, innerRadius, angle, POS_Z, 0.0f);
		//Outside
		addCircleVertices3D(vertices, loadTextureCoordinates, -0.5f, numPoints, 0.5f, angle, CIRCLE_X_Y, 0.0f);
		addCircleVertices3D(vertices, loadTextureCoordinates, 0.5f, numPoints, 0.5f, angle, CIRCLE_X_Y, 0.0f);
		//Inside
		addCircleVertices3D(vertices, loadTextureCoordinates, -0.5f, numPoints, innerRadius, angle, CIRCLE_X_Y_INVERTED, 0.0f);
		addCircleVertices3D(vertices, loadTextureCoordinates, 0.5f, numPoints, innerRadius, angle, CIRCLE_X_Y_INVERTED, 0.0f);
		//Fills
		if (angle != 360.0f) {
			addQuadVertices3D(vertices, loadTextureCoordinates, loadNormals, -0.5f, 0.5f, numPoints, innerRadius, 0.0f, false);
			addQuadVertices3D(vertices, loadTextureCoordinates, loadNormals, -0.5f, 0.5f, numPoints, innerRadius, angle, true);
		}
	}
	else {
		addCircleVertices3D(vertices, loadTextureCoordinates, -0.5f, numPoints, innerRadius, angle,NONE, 0.0f);
		addCircleVertices3D(vertices, loadTextureCoordinates, -0.5f, numPoints, 0.5f, angle,NONE, 0.0f);
		addCircleVertices3D(vertices, loadTextureCoordinates, 0.5f, numPoints, innerRadius, angle,NONE, 0.0f);
		addCircleVertices3D(vertices, loadTextureCoordinates, 0.5f, numPoints, 0.5f, angle,NONE, 0.0f);
	}
}

void HollowCylinder3D::getIndices(std::vector<unsigned int>& indices, bool loadTextureCoordinates, bool loadNormals, int numPoints, float angle, float innerRadius, int numRings) {
	if (loadNormals) {
		//Back
		addCircleRingIndices(indices, numPoints, angle, 0, numPoints, false);
		//Front
		addCircleRingIndices(indices, numPoints, angle, 2*numPoints, 3*numPoints, false);
		//Outside
		addCircleRingIndices(indices, numPoints, angle, 4 * numPoints, 5 * numPoints, false);
		//Inside
		addCircleRingIndices(indices, numPoints, angle, 6 * numPoints, 7 * numPoints, false);
	}
	else {
		addCircleRingIndices(indices, numPoints, angle, 0, numPoints , false);
		addCircleRingIndices(indices, numPoints, angle, 2*numPoints, 3*numPoints, true);
		addCircleRingIndices(indices, numPoints, angle, numPoints, 3*numPoints, false);
		addCircleRingIndices(indices, numPoints, angle, 0, 2*numPoints, true);
	}

	if (angle != 360.0f) {
		if (loadNormals) {
			addQuadIndices(indices, 8 * numPoints, 8 * numPoints + 1, 8 * numPoints + 2, 8 * numPoints + 3, true);
			addQuadIndices(indices, 8 * numPoints + 4, 8 * numPoints + 7, 8 * numPoints + 6, 8 * numPoints + 5, true);
		}
		else {
			addQuadIndices(indices, 0, numPoints, 3 * numPoints, 2 * numPoints, true);
			addQuadIndices(indices, 2 * numPoints - 1, numPoints - 1, 3 * numPoints - 1, 4 * numPoints - 1, true);
		}
	}
}