#include "Geometry.h"

void Geometry2D::addVertex2D(std::vector<float>& vertices, float x,float y){
	vertices.push_back(x);
	vertices.push_back(y);
}

void Geometry3D::addVertex3D(std::vector<float>& vertices, float x, float y, float z) {
	vertices.push_back(x);
	vertices.push_back(y);
	vertices.push_back(z);
}

void Geometry::addTextureCoordinate(std::vector<float>& vertices, float u, float v) {
	vertices.push_back(u);
	vertices.push_back(v);
}

void Geometry3D::addNormal(std::vector<float>& vertices, NormalMode normalMode,float angle,float normalZ) {
	float x, y, z;
	float length;
	switch (normalMode) {
	case NONE:
		break;
	case POS_X:
		vertices.push_back(1.0f);
		vertices.push_back(0.0f);
		vertices.push_back(0.0f);
		break;
	case NEG_X:
		vertices.push_back(-1.0f);
		vertices.push_back(0.0f);
		vertices.push_back(0.0f);
		break;
	case POS_Y:
		vertices.push_back(0.0f);
		vertices.push_back(1.0f);
		vertices.push_back(0.0f);
		break;
	case NEG_Y:
		vertices.push_back(0.0f);
		vertices.push_back(-1.0f);
		vertices.push_back(0.0f);
		break;
	case POS_Z:
		vertices.push_back(0.0f);
		vertices.push_back(0.0f);
		vertices.push_back(1.0f);
		break;
	case NEG_Z:
		vertices.push_back(0.0f);
		vertices.push_back(0.0f);
		vertices.push_back(-1.0f);
		break;
	case CIRCLE_X_Y:
		x= sin(M_PI / 180.0f * angle);
		y= cos(M_PI / 180.0f * angle);
		z=normalZ;
		length = sqrt(x*x+y*y+z*z);
		x = x / length;
		y = y / length;
		z = z / length;
		vertices.push_back(x);
		vertices.push_back(y);
		vertices.push_back(z);
		break;
	case CIRCLE_X_Y_INVERTED:
		x = -sin(M_PI / 180.0f * angle);
		y = -cos(M_PI / 180.0f * angle);
		z = normalZ;
		length = sqrt(x * x + y * y + z * z);
		x = x / length;
		y = y / length;
		z = z / length;
		vertices.push_back(x);
		vertices.push_back(y);
		vertices.push_back(z);
		break;
	case CIRCLE_X_Y_90:
		x = cos(M_PI / 180.0f * angle);
		y = -sin(M_PI / 180.0f * angle);
		z = normalZ;
		length = sqrt(x * x + y * y + z * z);
		x = x / length;
		y = y / length;
		z = z / length;
		vertices.push_back(x);
		vertices.push_back(y);
		vertices.push_back(z);
		break;
	case CIRCLE_X_Y_90_INVERTED:
		x = -cos(M_PI / 180.0f * angle);
		y = sin(M_PI / 180.0f * angle);
		z = normalZ;
		length = sqrt(x * x + y * y + z * z);
		x = x / length;
		y = y / length;
		z = z / length;
		vertices.push_back(x);
		vertices.push_back(y);
		vertices.push_back(z);
		break;
	default:
		break;
	}
}

void Geometry3D::addQuadVertices3D(std::vector<float>& vertices, bool loadTextureCoordinates, bool loadNormals, float z1, float z2, int numPoints, float innerRadius, float angle,bool flipNormals){
	float s = sin(M_PI / 180.0f * angle);
	float c = cos(M_PI / 180.0f * angle);

	//Mitte1
	vertices.push_back(innerRadius * s);
	vertices.push_back(innerRadius * c);
	vertices.push_back(z1);
	if (loadTextureCoordinates) {
		addTextureCoordinate(vertices, 0.5f + innerRadius * s, 0.5f - innerRadius * c);
	}
	if (loadNormals) {
		if (flipNormals) {
			addNormal(vertices, CIRCLE_X_Y_90, angle, 0.0f);
		}
		else {
			addNormal(vertices, CIRCLE_X_Y_90_INVERTED, angle, 0.0f);
		}
	}

	//Auﬂen1
	vertices.push_back(0.5f*s);
	vertices.push_back(0.5f *c);
	vertices.push_back(z1);
	if (loadTextureCoordinates) {
		addTextureCoordinate(vertices, 0.5f+ 0.5f *s, 0.5f- 0.5f *c);
	}
	if (loadNormals) {
		if (flipNormals) {
			addNormal(vertices, CIRCLE_X_Y_90, angle, 0.0f);
		}
		else {
			addNormal(vertices, CIRCLE_X_Y_90_INVERTED, angle, 0.0f);
		}
	}

	//Auﬂen1
	vertices.push_back(0.5f * s);
	vertices.push_back(0.5f * c);
	vertices.push_back(z2);
	if (loadTextureCoordinates) {
		addTextureCoordinate(vertices, 0.5f + 0.5f * s, 0.5f - 0.5f * c);
	}
	if (loadNormals) {
		if (flipNormals) {
			addNormal(vertices, CIRCLE_X_Y_90, angle, 0.0f);
		}
		else {
			addNormal(vertices, CIRCLE_X_Y_90_INVERTED, angle, 0.0f);
		}
	}

	//Mitte2
	vertices.push_back(innerRadius * s);
	vertices.push_back(innerRadius * c);
	vertices.push_back(z2);
	if (loadTextureCoordinates) {
		addTextureCoordinate(vertices, 0.5f + innerRadius * s, 0.5f - innerRadius * c);
	}
	if (loadNormals) {
		if (flipNormals) {
			addNormal(vertices, CIRCLE_X_Y_90, angle, 0.0f);
		}
		else {
			addNormal(vertices, CIRCLE_X_Y_90_INVERTED, angle, 0.0f);
		}
	}
}

void Geometry3D::addTriangleVertices3D(std::vector<float>& vertices, bool loadTextureCoordinates, bool loadNormals, float z1, float z2, int numPoints, float innerRadius, float angle, bool flipNormals) {
	float s = sin(M_PI / 180.0f * angle);
	float c = cos(M_PI / 180.0f * angle);

	//Mitte1
	vertices.push_back(innerRadius * s);
	vertices.push_back(innerRadius * c);
	vertices.push_back(z1);
	if (loadTextureCoordinates) {
		addTextureCoordinate(vertices, 0.5f + innerRadius * s, 0.5f - innerRadius * c);
	}
	if (loadNormals) {
		if (flipNormals) {
			addNormal(vertices, CIRCLE_X_Y_90, angle, 0.0f);
		}
		else {
			addNormal(vertices, CIRCLE_X_Y_90_INVERTED, angle, 0.0f);
		}
	}

	//Auﬂen1
	vertices.push_back(0.5f * s);
	vertices.push_back(0.5f * c);
	vertices.push_back(z1);
	if (loadTextureCoordinates) {
		addTextureCoordinate(vertices, 0.5f + 0.5f * s, 0.5f - 0.5f * c);
	}
	if (loadNormals) {
		if (flipNormals) {
			addNormal(vertices, CIRCLE_X_Y_90, angle, 0.0f);
		}
		else {
			addNormal(vertices, CIRCLE_X_Y_90_INVERTED, angle, 0.0f);
		}
	}

	//Mitte2
	vertices.push_back(innerRadius * s);
	vertices.push_back(innerRadius * c);
	vertices.push_back(z2);
	if (loadTextureCoordinates) {
		addTextureCoordinate(vertices, 0.5f + innerRadius * s, 0.5f - innerRadius * c);
	}
	if (loadNormals) {
		if (flipNormals) {
			addNormal(vertices, CIRCLE_X_Y_90, angle, 0.0f);
		}
		else {
			addNormal(vertices, CIRCLE_X_Y_90_INVERTED, angle, 0.0f);
		}
	}
}

void Geometry2D::addCircleVertices2D(std::vector<float>& vertices, bool loadTextureCoordinates, int numPoints,float radius, float angle){
	float da = 0;
	if (angle == 360.0f) {
		da = angle / numPoints;
	}
	else {
		da = angle / (numPoints - 1);
	}

	for (int i = 0; i < numPoints; i++) {
		vertices.push_back(0.5f + radius * sin(M_PI / 180.0f * i * da));
		vertices.push_back(0.5f + radius * cos(M_PI / 180.0f * i * da));

		if (loadTextureCoordinates) {
			vertices.push_back(0.5f + radius*sin(M_PI / 180.0f * i * da));
			vertices.push_back(0.5f + radius*cos(M_PI / 180.0f * i * da));
		}
	}
}

void Geometry3D::addCircleVertices3D(std::vector<float>& vertices, bool loadTextureCoordinates, float z, int numPoints, float radius, float angle,NormalMode normalMode,float normalZ) {
	float da = 0;
	if (angle == 360.0f) {
		da = angle / numPoints;
	}
	else {
		da = angle / (numPoints - 1);
	}

	for (int i = 0; i < numPoints; i++) {
		vertices.push_back(radius * sin(M_PI / 180.0f * i * da));
		vertices.push_back(radius * cos(M_PI / 180.0f * i * da));
		vertices.push_back(z);

		if (loadTextureCoordinates) {
			vertices.push_back(0.5f + radius * sin(M_PI / 180.0f * i * da));
			vertices.push_back(0.5f - radius * cos(M_PI / 180.0f * i * da));
		}

		addNormal(vertices,normalMode,i*da,normalZ);
	}
}

void Geometry::addCircleIndices(std::vector<unsigned int>& indices,int numPoints,float angle,int center,int start, bool flip){
	for (int i = 0; i < numPoints - 1; i++) {
		if (flip) {
			indices.push_back(i + start);
			indices.push_back(center);
			indices.push_back(i + start + 1);
		}
		else {
			indices.push_back(center);
			indices.push_back(i + start);
			indices.push_back(i + start + 1);
		}
	}

	if (angle == 360.0f) {
		if (flip) {
			indices.push_back(start + numPoints - 1);
			indices.push_back(center);
			indices.push_back(start);
		}
		else {
			indices.push_back(center);
			indices.push_back(start + numPoints - 1);
			indices.push_back(start);
		}
	}
}

void Geometry::addCircleRingIndices(std::vector<unsigned int>& indices, int numPoints, float angle, int start1, int start2, bool flip){
	for (int i = 0; i < numPoints - 1; i++) {
		if (flip) {
			//First triangle
			indices.push_back(start2 + i + 1);
			indices.push_back(start1 + i);
			indices.push_back(start1 + i + 1);

			//Second triangle
			indices.push_back(start2 + i);
			indices.push_back(start1 + i);
			indices.push_back(start2 + i + 1);
		}
		else {
			//First triangle
			indices.push_back(start1 + i);
			indices.push_back(start2 + i + 1);
			indices.push_back(start1 + i + 1);

			//Second triangle
			indices.push_back(start1 + i);
			indices.push_back(start2 + i);
			indices.push_back(start2 + i + 1);
		}
	}

	if (angle == 360.0f) {
		if (flip) {
			//First triangle
			indices.push_back(start2);
			indices.push_back(start1 + numPoints - 1);
			indices.push_back(start1);
			
			//Second triangle
			indices.push_back(start2 + numPoints - 1);
			indices.push_back(start1 + numPoints - 1);
			indices.push_back(start2);
		}
		else {
			//First triangle
			indices.push_back(start1 + numPoints - 1);
			indices.push_back(start2);
			indices.push_back(start1);

			//Second triangle
			indices.push_back(start1 + numPoints - 1);
			indices.push_back(start2 + numPoints - 1);
			indices.push_back(start2);
		}
	}
}

void Geometry::addTriangleIndices(std::vector<unsigned int>& indices, int i1, int i2, int i3, bool flip) {
	if (flip) {
		indices.push_back(i2);
		indices.push_back(i1);
		indices.push_back(i3);
	}
	else {
		indices.push_back(i1);
		indices.push_back(i2);
		indices.push_back(i3);
	}
}

void Geometry::addQuadIndices(std::vector<unsigned int>& indices, int i1, int i2, int i3, int i4, bool flip) {
	if (flip) {
		indices.push_back(i2);
		indices.push_back(i1);
		indices.push_back(i3);

		indices.push_back(i3);
		indices.push_back(i1);
		indices.push_back(i4);
	}
	else {
		indices.push_back(i1);
		indices.push_back(i2);
		indices.push_back(i3);

		indices.push_back(i1);
		indices.push_back(i3);
		indices.push_back(i4);
	}
}