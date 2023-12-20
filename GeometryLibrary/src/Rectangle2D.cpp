#include "Geometry.h"

void Rectangle2D::getVertices(std::vector<float> &vertices, bool loadTextureCoordinates, bool loadNormals, int numPoints, float angle, float innerRadius, int numRings){
	if (loadTextureCoordinates) {
		addVertex2D(vertices, 0.0f, 0.0f); addTextureCoordinate(vertices, 0.0f, 0.0f);
		addVertex2D(vertices, 0.0f, 1.0f); addTextureCoordinate(vertices, 0.0f, 1.0f);
		addVertex2D(vertices, 1.0f, 1.0f); addTextureCoordinate(vertices, 1.0f, 1.0f);
		addVertex2D(vertices, 1.0f, 0.0f); addTextureCoordinate(vertices, 1.0f, 0.0f);
	}
	else {
		addVertex2D(vertices, 0.0f, 0.0f);
		addVertex2D(vertices, 0.0f, 1.0f);
		addVertex2D(vertices, 1.0f, 1.0f);
		addVertex2D(vertices, 1.0f, 0.0f);
	}
}

void Rectangle2D::getIndices(std::vector<unsigned int> &indices, bool loadTextureCoordinates, bool loadNormals, int numPoints, float angle, float innerRadius, int numRings){
	addQuadIndices(indices, 0, 1, 2, 3,false);
}