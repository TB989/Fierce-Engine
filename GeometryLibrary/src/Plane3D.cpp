#include "Geometry.h"

void Plane3D::getVertices(std::vector<float>& vertices, bool loadTextureCoordinates, bool loadNormals, int numPoints, float angle, float innerRadius, int numRings) {
	if (loadTextureCoordinates && loadNormals) {
		addVertex3D(vertices, -0.5f, 0, -0.5f); addTextureCoordinate(vertices, 0.0f, 0.0f); addNormal(vertices, POS_Y,0.0f,0.0f);
		addVertex3D(vertices, -0.5f, 0,  0.5f); addTextureCoordinate(vertices, 0.0f, 1.0f); addNormal(vertices, POS_Y, 0.0f, 0.0f);
		addVertex3D(vertices,  0.5f, 0,  0.5f); addTextureCoordinate(vertices, 1.0f, 1.0f); addNormal(vertices, POS_Y, 0.0f, 0.0f);
		addVertex3D(vertices,  0.5f, 0, -0.5f); addTextureCoordinate(vertices, 1.0f, 0.0f); addNormal(vertices, POS_Y, 0.0f, 0.0f);
	}
	else if (loadTextureCoordinates) {
		addVertex3D(vertices, -0.5f, 0, -0.5f); addTextureCoordinate(vertices, 0.0f, 0.0f); 
		addVertex3D(vertices, -0.5f, 0,  0.5f); addTextureCoordinate(vertices, 0.0f, 1.0f); 
		addVertex3D(vertices,  0.5f, 0,  0.5f); addTextureCoordinate(vertices, 1.0f, 1.0f); 
		addVertex3D(vertices,  0.5f, 0, -0.5f); addTextureCoordinate(vertices, 1.0f, 0.0f); 
	}
	else if (loadNormals) {
		addVertex3D(vertices, -0.5f, 0, -0.5f); addNormal(vertices, POS_Y, 0.0f, 0.0f);
		addVertex3D(vertices, -0.5f, 0,  0.5f); addNormal(vertices, POS_Y, 0.0f, 0.0f);
		addVertex3D(vertices,  0.5f, 0,  0.5f); addNormal(vertices, POS_Y, 0.0f, 0.0f);
		addVertex3D(vertices,  0.5f, 0, -0.5f); addNormal(vertices, POS_Y, 0.0f, 0.0f);
	}
	else {
		addVertex3D(vertices, -0.5f, 0, -0.5f);
		addVertex3D(vertices, -0.5f, 0,  0.5f);
		addVertex3D(vertices,  0.5f, 0,  0.5f);
		addVertex3D(vertices,  0.5f, 0, -0.5f);
	}
}

void Plane3D::getIndices(std::vector<unsigned int>& indices, bool loadTextureCoordinates, bool loadNormals, int numPoints, float angle, float innerRadius, int numRings) {
	addQuadIndices(indices,0,1,2,3,false);
}