#include "Geometry.h"

void Circle2D::getVertices(std::vector<float>& vertices, bool loadTextureCoordinates,bool loadNormals,int numPoints, float angle, float innerRadius, int numRings) {
	if (loadTextureCoordinates) {
		addVertex2D(vertices, 0.5f, 0.5f); addTextureCoordinate(vertices, 0.5f, 0.5f);
	}
	else {
		addVertex2D(vertices, 0.5f, 0.5f);
	}
	addCircleVertices2D(vertices,loadTextureCoordinates,numPoints,0.5f,angle);
}

void Circle2D::getIndices(std::vector<unsigned int>& indices, bool loadTextureCoordinates, bool loadNormals, int numPoints, float angle, float innerRadius, int numRings) {
	addCircleIndices(indices, numPoints, angle, 0, 1,false);
}