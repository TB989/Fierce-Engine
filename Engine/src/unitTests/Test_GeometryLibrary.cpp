#include "UnitTests.h"

#include "src/utils/Logging.h"

Test_GeometryLibrary::Test_GeometryLibrary() {

}

void Test_GeometryLibrary::init() {
	renderer_setOrthographicProjection(800,600,-1,1);

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
	rectangle_meshId = renderer_loadMesh(MeshSettings{true,false,false,false}, vertices.size(), vertices.data(), indices.size(), indices.data());
	rectangle_color = new Color3f(0.0f, 1.0f, 0.0f);
	rectangle_modelMatrix = new Mat4();
	rectangle_modelMatrix->scale(100.0f, 100.0f, 0.0f);
	rectangle_modelMatrix->translate(10.0f, 10.0f, 0.0f);

	vertices.clear();
	indices.clear();

	loader->loadGeometry(GeometrySettings{ CIRCLE,5,360.0f,0.0f,0 }, vertices, indices);
	circle_meshId = renderer_loadMesh(MeshSettings{ true,false,false,false }, vertices.size(), vertices.data(), indices.size(), indices.data());
	circle_color = new Color3f(1.0f, 0.0f, 0.0f);
	circle_modelMatrix = new Mat4();
	circle_modelMatrix->scale(100.0f, 100.0f, 0.0f);
	circle_modelMatrix->translate(120.0f, 10.0f, 0.0f);

	vertices.clear();
	indices.clear();

	loader->loadGeometry(GeometrySettings{ TRIANGLE,0,0.0f,0.0f,0 }, vertices, indices);
	triangle_meshId = renderer_loadMesh(MeshSettings{ true,false,false,false }, vertices.size(), vertices.data(), indices.size(), indices.data());
	triangle_color = new Color3f(1.0f, 0.0f, 1.0f);
	triangle_modelMatrix = new Mat4();
	triangle_modelMatrix->scale(100.0f, 100.0f, 0.0f);
	triangle_modelMatrix->translate(230.0f, 10.0f, 0.0f);

	vertices.clear();
	indices.clear();

	loader->loadGeometry(GeometrySettings{ CIRCLE_RING,32,360.0f,0.25f,0 }, vertices, indices);
	circleRing_meshId = renderer_loadMesh(MeshSettings{ true,false,false,false }, vertices.size(), vertices.data(), indices.size(), indices.data());
	circleRing_color = new Color3f(1.0f, 1.0f, 0.0f);
	circleRing_modelMatrix = new Mat4();
	circleRing_modelMatrix->scale(100.0f, 100.0f, 0.0f);
	circleRing_modelMatrix->translate(340.0f, 10.0f, 0.0f);

	vertices.clear();
	indices.clear();

	loader->loadGeometry(GeometrySettings{ PLANE,0,0.0f,0.0f,0 }, vertices, indices);
	plane_meshId = renderer_loadMesh(MeshSettings{ false,false,false,false }, vertices.size(), vertices.data(), indices.size(), indices.data());
	plane_color = new Color3f(1.0f, 0.0f, 0.0f);
	plane_modelMatrix = new Mat4();
	plane_modelMatrix->scale(1000.0f, 1.0f, 1000.0f);
	plane_modelMatrix->translate(0.0f, -2.0f, 0.0f);
}

void Test_GeometryLibrary::update() {

}

void Test_GeometryLibrary::doRender() {
	Mat4* viewMatrix = new Mat4();
	viewMatrix->setToView(Transform3D(0,0,0,1,1,1,45,0,0));
	renderer_setViewMatrix(viewMatrix->get());

	renderer_addEntity(RenderType::SIMPLE_COLOR_2D, rectangle_modelMatrix->get(), rectangle_meshId, rectangle_color->get());
	renderer_addEntity(RenderType::SIMPLE_COLOR_2D, circle_modelMatrix->get(), circle_meshId, circle_color->get());
	renderer_addEntity(RenderType::SIMPLE_COLOR_2D, triangle_modelMatrix->get(), triangle_meshId, triangle_color->get());
	renderer_addEntity(RenderType::SIMPLE_COLOR_2D, circleRing_modelMatrix->get(), circleRing_meshId, circleRing_color->get());

	renderer_addEntity(RenderType::SIMPLE_COLOR_3D, plane_modelMatrix->get(), plane_meshId, plane_color->get());
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