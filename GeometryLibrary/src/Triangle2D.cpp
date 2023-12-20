#include "Geometry.h"

void Triangle2D::getVertices(std::vector<float>& vertices, bool loadTextureCoordinates,bool loadNormals,int numPoints, float angle, float innerRadius, int numRings) {
	if (loadTextureCoordinates) {
		addVertex2D(vertices, 0.0f, 0.0f); addTextureCoordinate(vertices,0.0f, 0.0f);
		addVertex2D(vertices, 0.5f, 1.0f); addTextureCoordinate(vertices, 0.5f, 1.0f);
		addVertex2D(vertices, 1.0f, 0.0f); addTextureCoordinate(vertices, 1.0f, 0.0f);
	}
	else {
		addVertex2D(vertices, 0.0f, 0.0f);
		addVertex2D(vertices, 0.5f, 1.0f);
		addVertex2D(vertices, 1.0f, 0.0f);
	}
}

void Triangle2D::getIndices(std::vector<unsigned int>& indices, bool loadTextureCoordinates, bool loadNormals, int numPoints, float angle, float innerRadius, int numRings) {
	addTriangleIndices(indices,0, 1, 2,false);
}