#include "Geometry.h"

void Cube3D::getVertices(std::vector<float>& vertices, bool loadTextureCoordinates, bool loadNormals, int numPoints, float angle, float innerRadius, int numRings) {
	if (loadTextureCoordinates) {
		//Bottom
		addVertex3D(vertices, 0.5f, -0.5f, 0.5f, 0.0f, 1.0f);
		addVertex3D(vertices, -0.5f, -0.5f, 0.5f, 1.0f, 1.0f);
		addVertex3D(vertices, -0.5f, -0.5f, -0.5f, 1.0f, 0.0f);
		addVertex3D(vertices, 0.5f, -0.5f, -0.5f, 0.0f, 0.0f);

		//Front
		addVertex3D(vertices, -0.5f, -0.5f, 0.5f, 0.0f, 1.0f);
		addVertex3D(vertices, 0.5f, -0.5f, 0.5f, 1.0f, 1.0f);
		addVertex3D(vertices, 0.5f, 0.5f, 0.5f, 1.0f, 0.0f);
		addVertex3D(vertices, -0.5f, 0.5f, 0.5f, 0.0f, 0.0f);

		//Right
		addVertex3D(vertices, 0.5f, -0.5f, 0.5f, 0.0f, 1.0f);
		addVertex3D(vertices, 0.5f, -0.5f, -0.5f, 1.0f, 1.0f);
		addVertex3D(vertices, 0.5f, 0.5f, -0.5f, 1.0f, 0.0f);
		addVertex3D(vertices, 0.5f, 0.5f, 0.5f, 0.0f, 0.0f);

		//Back
		addVertex3D(vertices, 0.5f, -0.5f, -0.5f, 0.0f, 1.0f);
		addVertex3D(vertices, -0.5f, -0.5f, -0.5f, 1.0f, 1.0f);
		addVertex3D(vertices, -0.5f, 0.5f, -0.5f, 1.0f, 0.0f);
		addVertex3D(vertices, 0.5f, 0.5f, -0.5f, 0.0f, 0.0f);

		//Left
		addVertex3D(vertices, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f);
		addVertex3D(vertices, -0.5f, -0.5f, 0.5f, 1.0f, 1.0f);
		addVertex3D(vertices, -0.5f, 0.5f, 0.5f, 1.0f, 0.0f);
		addVertex3D(vertices, -0.5f, 0.5f, -0.5f, 0.0f, 0.0f);

		//Top
		addVertex3D(vertices, -0.5f, 0.5f, 0.5f, 0.0f, 1.0f);
		addVertex3D(vertices, 0.5f, 0.5f, 0.5f, 1.0f, 1.0f);
		addVertex3D(vertices, 0.5f, 0.5f, -0.5f, 1.0f, 0.0f);
		addVertex3D(vertices, -0.5f, 0.5f, -0.5f, 0.0f, 0.0f);
	}
	else {
		addVertex3D(vertices, -0.5f, -0.5f, 0.5f);
		addVertex3D(vertices, 0.5f, -0.5f, 0.5f);
		addVertex3D(vertices, 0.5f, -0.5f, -0.5f);
		addVertex3D(vertices, -0.5f, -0.5f, -0.5f);

		addVertex3D(vertices, -0.5f, 0.5f, 0.5f);
		addVertex3D(vertices, 0.5f, 0.5f, 0.5f);
		addVertex3D(vertices, 0.5f, 0.5f, -0.5f);
		addVertex3D(vertices, -0.5f, 0.5f, -0.5f);
	}
}

void Cube3D::getIndices(std::vector<unsigned int>& indices, bool loadTextureCoordinates, bool loadNormals, int numPoints, float angle, float innerRadius, int numRings) {
	if (loadTextureCoordinates) {
		//Bottom
		addQuadIndices(indices, 0, 1, 2, 3, false);

		addQuadIndices(indices, 4, 5, 6, 7, false);
		addQuadIndices(indices, 8, 9, 10, 11, false);
		addQuadIndices(indices, 12, 13, 14, 15, false);
		addQuadIndices(indices, 16, 17, 18, 19, false);

		//Top
		addQuadIndices(indices, 20, 21, 22, 23, false);
	}
	else {
		//Bottom
		addQuadIndices(indices, 3, 2, 1, 0, false);

		addQuadIndices(indices, 0, 1, 5, 4, false);
		addQuadIndices(indices, 1, 2, 6, 5, false);
		addQuadIndices(indices, 2, 3, 7, 6, false);
		addQuadIndices(indices, 3, 0, 4, 7, false);

		//Top
		addQuadIndices(indices, 4, 5, 6, 7, false);
	}
}