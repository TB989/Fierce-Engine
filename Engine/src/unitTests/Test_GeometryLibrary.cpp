#include "UnitTests.h"

#include "src/utils/Logging.h"

Test_GeometryLibrary::Test_GeometryLibrary() {

}

void Test_GeometryLibrary::init() {
	loader = new GeometryLoader();

	loader->registerGeometry(RECTANGLE, new Rectangle2D());
	loader->registerGeometry(TRIANGLE, new Triangle2D());
	loader->registerGeometry(CIRCLE, new Circle2D());
	loader->registerGeometry(CIRCLE_RING, new CircleRing2D());

	loader->registerGeometry(PLANE, new Plane3D());
	loader->registerGeometry(CUBE, new Cube3D());
	loader->registerGeometry(CONE, new Cone3D());
	loader->registerGeometry(CYLINDER, new Cylinder3D());
	loader->registerGeometry(HOLLOW_CYLINDER, new HollowCylinder3D());
	loader->registerGeometry(SPHERE, new Sphere3D());

	std::vector<float> vertices;
	std::vector<unsigned int> indices;

	loader->loadGeometry(GeometrySettings{ RECTANGLE,0,0.0f,0.0f,0 }, vertices, indices);

	int id = renderer_loadMesh(MeshSettings{true,false,false,false}, vertices.size(), vertices.data(), indices.size(), indices.data());
}

void Test_GeometryLibrary::update() {

}

void Test_GeometryLibrary::doRender() {

}

void Test_GeometryLibrary::cleanUp() {
	loader->unregisterGeometry(RECTANGLE);
	loader->unregisterGeometry(TRIANGLE);
	loader->unregisterGeometry(CIRCLE);
	loader->unregisterGeometry(CIRCLE_RING);

	loader->unregisterGeometry(PLANE);
	loader->unregisterGeometry(CUBE);
	loader->unregisterGeometry(CONE);
	loader->unregisterGeometry(CYLINDER);
	loader->unregisterGeometry(HOLLOW_CYLINDER);
	loader->unregisterGeometry(SPHERE);

	delete loader;
}