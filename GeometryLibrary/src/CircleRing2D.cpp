#include "Geometry.h"

void CircleRing2D::getVertices(std::vector<float>& vertices, bool loadTextureCoordinates,bool loadNormals, int numPoints, float angle, float innerRadius, int numRings) {
	addCircleVertices2D(vertices,loadTextureCoordinates, numPoints, innerRadius, angle);
	addCircleVertices2D(vertices,loadTextureCoordinates, numPoints, 0.5f,angle);
}

void CircleRing2D::getIndices(std::vector<unsigned int>& indices, bool loadTextureCoordinates, bool loadNormals, int numPoints, float angle, float innerRadius, int numRings) {
	addCircleRingIndices(indices,numPoints,angle,0,numPoints,false);
}