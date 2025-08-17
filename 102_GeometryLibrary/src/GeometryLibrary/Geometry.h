#pragma once

#include <vector>

#define _USE_MATH_DEFINES
#include <math.h>

namespace Fierce {
	enum GeometryType {
		RECTANGLE,
		CIRCLE,
		CIRCLE_RING,
		TRIANGLE,

		PLANE,
		CUBE,
		CYLINDER,
		HOLLOW_CYLINDER,
		CONE,
		SPHERE
	};

	class Geometry {
	public:
		virtual void getVertices(std::vector<float>& vertices, int numPoints, float angle, float innerRadius, int numRings) = 0;
		virtual void getIndices(std::vector<uint16_t>& indices, int numPoints, float angle, float innerRadius, int numRings) = 0;
	protected:
		void addTriangleIndices(std::vector<uint16_t>& indices, int i1, int i2, int i3, bool flip);
		void addQuadIndices(std::vector<uint16_t>& indices, int i1, int i2, int i3, int i4, bool flip);
		void addCircleIndices(std::vector<uint16_t>& indices, int numPoints, float angle, int center, int start, bool flip);
		void addCircleRingIndices(std::vector<uint16_t>& indices, int numPoints, float angle, int start1, int start2, bool flip);
	};

	class Geometry2D :public Geometry {
	protected:
		void addVertex2D(std::vector<float>& vertices, float x, float y);
		void addCircleVertices2D(std::vector<float>& vertices, float x, float y, int numPoints, float radius, float angle);
	};

	class Rectangle2D :public Geometry2D {
	public:
		void getVertices(std::vector<float>& vertices, int numPoints, float angle, float innerRadius, int numRings);
		void getIndices(std::vector<uint16_t>& indices, int numPoints, float angle, float innerRadius, int numRings);
	};

	class Circle2D :public Geometry2D {
	public:
		void getVertices(std::vector<float>& vertices, int numPoints, float angle, float innerRadius, int numRings);
		void getIndices(std::vector<uint16_t>& indices, int numPoints, float angle, float innerRadius, int numRings);
	};

	class CircleRing2D :public Geometry2D {
	public:
		void getVertices(std::vector<float>& vertices, int numPoints, float angle, float innerRadius, int numRings);
		void getIndices(std::vector<uint16_t>& indices, int numPoints, float angle, float innerRadius, int numRings);
	};

	class Triangle2D :public Geometry2D {
	public:
		void getVertices(std::vector<float>& vertices, int numPoints, float angle, float innerRadius, int numRings);
		void getIndices(std::vector<uint16_t>& indices, int numPoints, float angle, float innerRadius, int numRings);
	};

	class Geometry3D :public Geometry {
	protected:
		void addVertex3D(std::vector<float>& vertices, float x, float y, float z);
		void addCircleVertices3D(std::vector<float>& vertices, float x, float y, float z, int numPoints, float radius, float angle);
	};

	class Plane3D :public Geometry3D {
	public:
		void getVertices(std::vector<float>& vertices, int numPoints, float angle, float innerRadius, int numRings);
		void getIndices(std::vector<uint16_t>& indices, int numPoints, float angle, float innerRadius, int numRings);
	};

	class Cube3D :public Geometry3D {
	public:
		void getVertices(std::vector<float>& vertices, int numPoints, float angle, float innerRadius, int numRings);
		void getIndices(std::vector<uint16_t>& indices, int numPoints, float angle, float innerRadius, int numRings);
	};

	class Cylinder3D :public Geometry3D {
	public:
		void getVertices(std::vector<float>& vertices, int numPoints, float angle, float innerRadius, int numRings);
		void getIndices(std::vector<uint16_t>& indices, int numPoints, float angle, float innerRadius, int numRings);
	};

	class HollowCylinder3D :public Geometry3D {
	public:
		void getVertices(std::vector<float>& vertices, int numPoints, float angle, float innerRadius, int numRings);
		void getIndices(std::vector<uint16_t>& indices, int numPoints, float angle, float innerRadius, int numRings);
	};

	class Cone3D :public Geometry3D {
	public:
		void getVertices(std::vector<float>& vertices, int numPoints, float angle, float innerRadius, int numRings);
		void getIndices(std::vector<uint16_t>& indices, int numPoints, float angle, float innerRadius, int numRings);
	};

	class Sphere3D :public Geometry3D {
	public:
		void getVertices(std::vector<float>& vertices, int numPoints, float angle, float innerRadius, int numRings);
		void getIndices(std::vector<uint16_t>& indices, int numPoints, float angle, float innerRadius, int numRings);
	};
}//end namespace