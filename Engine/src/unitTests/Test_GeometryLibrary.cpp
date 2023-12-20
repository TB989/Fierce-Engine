#include "UnitTests.h"

#include "src/utils/Logging.h"

#include "src/actions/Action_StopEngine.h"
#include "src/actions/Action_LookRightLeft.h"
#include "src/actions/Action_LookUpDown.h"
#include "src/actions/Action_MoveForward.h"
#include "src/actions/Action_MoveBackward.h"

#define STB_IMAGE_IMPLEMENTATION
#include "src/io/textures/stb_image.h"

/**void Test_GeometryLibrary::onKeyDown(KeyDownEvent* event) {
	if (event->m_key == 'W') {
		Vector3f* angles = camera->getRotation();
		Vector3f* position = camera->getPosition();

		float angleY = angles->getY();
		float s = sin(M_PI / 180.0f * angleY);
		float c = cos(M_PI / 180.0f * angleY);
		position->setX(position->getX() + s * 0.3f);
		position->setZ(position->getZ() - c * 0.3f);
		//LOGGER->info("New position: %1.3f %1.3f %1.3f",position->getX(),position->getY(),position->getZ());
	}

	if (event->m_key == 'S') {
		Vector3f* angles = camera->getRotation();
		Vector3f* position = camera->getPosition();

		float angleY = angles->getY();
		float s = sin(M_PI / 180.0f * angleY);
		float c = cos(M_PI / 180.0f * angleY);
		position->setX(position->getX() - s * 0.3f);
		position->setZ(position->getZ() + c * 0.3f);
		//LOGGER->info("New position: %1.3f %1.3f %1.3f", position->getX(), position->getY(), position->getZ());
	}
}

void Test_GeometryLibrary::onMouseMoved(MouseMoveEvent* event) {
	if (first) {
		m_x_alt = event->m_x;
		m_y_alt = event->m_y;
		first = false;
		return;
	}

	int dx = m_x_alt - event->m_x;
	int dy = m_y_alt - event->m_y;

	Vector3f* angles=camera->getRotation();

	float angleX = angles->getX() - 0.3f * dy;
	if (angleX > 45.0f) {
		angleX = 45.0f;
	}
	if (angleX < -45.0f) {
		angleX = -45.0f;
	}
	angles->setX(angleX);

	float angleY = angles->getY() - 0.3f * dx;
	angles->setY(angleY);

	m_x_alt = event->m_x;
	m_y_alt = event->m_y;

	//LOGGER->info("New rotations: %1.3f %1.3f %1.3f", angles->getX(), angles->getY(), angles->getZ());
}*/


Test_GeometryLibrary::Test_GeometryLibrary() {
	
}

void Test_GeometryLibrary::init(World* world) {
	//eventSystem->addListener(this, &Test_GeometryLibrary::onKeyDown);
	//eventSystem->addListener(this, &Test_GeometryLibrary::onMouseMoved);

	LOGGER->error("Start init");
	setupCamera();
	loadTextures();
	addActions();
	setProjectionMatrices();

	Mat4 matrix;

	planeColored = world->createEntity();
	//world->addComponent(planeColored, GeometrySettings{RECTANGLE,0,0.0f,0.0f,0});
	//world->addComponent(planeColored, MeshSettings{true,false,true,false});

	Color3f tempColor = { 0.0f, 1.0f, 0.0f };
	LOGGER->error("Before add");
	world->addComponent(planeColored, tempColor);

	matrix = Mat4();
	matrix.scale(100.0f, 100.0f, 0.0f);
	matrix.translate(10.0f, 10.0f, 0.0f);
	//world->addComponent(planeColored, matrix);

	world->removeComponent<GeometrySettings>(planeColored);
	world->removeComponent<MeshSettings>(planeColored);
	world->removeComponent<Mat4>(planeColored);
	world->removeComponent<Color3f>(planeColored);
	world->destroyEntity(planeColored);


	LOGGER->error("End of init");


	/**loader = new GeometryLoader();

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

	loader->loadGeometry(GeometrySettings{ RECTANGLE,0,0.0f,0.0f,0 }, true,false,vertices, indices);
	rectangle_meshId = renderer_loadMesh(MeshSettings{true,false,true,false}, vertices.size(), vertices.data(), indices.size(), indices.data());
	rectangle_color = new Color3f(0.0f, 1.0f, 0.0f);
	rectangle_modelMatrix = new Mat4();
	rectangle_modelMatrix->scale(100.0f, 100.0f, 0.0f);
	rectangle_modelMatrix->translate(10.0f, 10.0f, 0.0f);
	rectangle_modelMatrixTexture = new Mat4();
	rectangle_modelMatrixTexture->scale(100.0f, 100.0f,0.0f);
	rectangle_modelMatrixTexture->translate(10.0f, 120.0f, 0.0f);

	vertices.clear();
	indices.clear();

	loader->loadGeometry(GeometrySettings{ CIRCLE,5,360.0f,0.0f,0 }, true,false,vertices, indices);
	circle_meshId = renderer_loadMesh(MeshSettings{ true,false,true,false }, vertices.size(), vertices.data(), indices.size(), indices.data());
	circle_color = new Color3f(1.0f, 0.0f, 0.0f);
	circle_modelMatrix = new Mat4();
	circle_modelMatrix->scale(100.0f, 100.0f, 0.0f);
	circle_modelMatrix->translate(120.0f, 10.0f, 0.0f);
	circle_modelMatrixTexture = new Mat4();
	circle_modelMatrixTexture->scale(100.0f, 100.0f, 0.0f);
	circle_modelMatrixTexture->translate(120.0f, 120.0f, 0.0f);

	vertices.clear();
	indices.clear();

	loader->loadGeometry(GeometrySettings{ TRIANGLE,0,0.0f,0.0f,0 }, true,false,vertices, indices);
	triangle_meshId = renderer_loadMesh(MeshSettings{ true,false,true,false }, vertices.size(), vertices.data(), indices.size(), indices.data());
	triangle_color = new Color3f(1.0f, 0.0f, 1.0f);
	triangle_modelMatrix = new Mat4();
	triangle_modelMatrix->scale(100.0f, 100.0f, 0.0f);
	triangle_modelMatrix->translate(230.0f, 10.0f, 0.0f);
	triangle_modelMatrixTexture = new Mat4();
	triangle_modelMatrixTexture->scale(100.0f, 100.0f, 0.0f);
	triangle_modelMatrixTexture->translate(230.0f, 120.0f, 0.0f);

	vertices.clear();
	indices.clear();

	loader->loadGeometry(GeometrySettings{ CIRCLE_RING,32,360.0f,0.1f,0 }, true,false,vertices, indices);
	circleRing_meshId = renderer_loadMesh(MeshSettings{ true,false,true,false }, vertices.size(), vertices.data(), indices.size(), indices.data());
	circleRing_color = new Color3f(1.0f, 1.0f, 0.0f);
	circleRing_modelMatrix = new Mat4();
	circleRing_modelMatrix->scale(100.0f, 100.0f, 0.0f);
	circleRing_modelMatrix->translate(340.0f, 10.0f, 0.0f);
	circleRing_modelMatrixTexture = new Mat4();
	circleRing_modelMatrixTexture->scale(100.0f, 100.0f, 0.0f);
	circleRing_modelMatrixTexture->translate(340.0f, 120.0f, 0.0f);

	vertices.clear();
	indices.clear();

	loader->loadGeometry(GeometrySettings{ PLANE,0,0.0f,0.0f,0 }, true,true,vertices, indices);
	plane_meshId = renderer_loadMesh(MeshSettings{ false,false,true,true }, vertices.size(), vertices.data(), indices.size(), indices.data());
	plane_color = new Color3f(1.0f, 1.0f, 1.0f);
	plane_modelMatrix = new Mat4();
	plane_modelMatrix->scale(1000.0f, 1.0f, 1000.0f);
	plane_modelMatrix->translate(0.0f, -2.0f, 0.0f);
	plane_modelMatrixTexture = new Mat4();
	plane_modelMatrixTexture->scale(10.0f, 1.0f, 10.0f);
	plane_modelMatrixTexture->translate(0.0f, -2.0f, 5.0f);

	vertices.clear();
	indices.clear();

	loader->loadGeometry(GeometrySettings{ CUBE,0,0.0f,0.0f,0 }, true,true,vertices, indices);
	cube_meshId = renderer_loadMesh(MeshSettings{ false,false,true,true }, vertices.size(), vertices.data(), indices.size(), indices.data());
	cube_color = new Color3f(1.0f, 0.0f, 0.0f);
	cube_modelMatrix = new Mat4();
	cube_modelMatrix->scale(2.0f, 2.0f, 2.0f);
	cube_modelMatrix->translate(0.0f, 0.0f, -10.0f);
	cube_modelMatrixTexture = new Mat4();
	cube_modelMatrixTexture->scale(2.0f, 2.0f, 2.0f);
	cube_modelMatrixTexture->translate(0.0f, 0.0f, -15.0f);

	vertices.clear();
	indices.clear();

	loader->loadGeometry(GeometrySettings{ CYLINDER,16,260.0f,0.0f,0 }, true, true, vertices, indices);
	cylinder_meshId = renderer_loadMesh(MeshSettings{ false,false,true,true }, vertices.size(), vertices.data(), indices.size(), indices.data());
	cylinder_color = new Color3f(1.0f, 0.0f, 0.0f);
	cylinder_modelMatrix = new Mat4();
	cylinder_modelMatrix->scale(2.0f, 2.0f, 2.0f);
	cylinder_modelMatrix->translate(5.0f, 0.0f, -10.0f);
	cylinder_modelMatrixTexture = new Mat4();
	cylinder_modelMatrixTexture->scale(2.0f, 2.0f, 2.0f);
	cylinder_modelMatrixTexture->translate(5.0f, 0.0f, -15.0f);

	vertices.clear();
	indices.clear();

	loader->loadGeometry(GeometrySettings{ HOLLOW_CYLINDER,16,260.0f,0.1f,0 }, true, true, vertices, indices);
	hollowCylinder_meshId = renderer_loadMesh(MeshSettings{ false,false,true,true }, vertices.size(), vertices.data(), indices.size(), indices.data());
	hollowCylinder_color = new Color3f(1.0f, 0.0f, 0.0f);
	hollowCylinder_modelMatrix = new Mat4();
	hollowCylinder_modelMatrix->scale(2.0f, 2.0f, 2.0f);
	hollowCylinder_modelMatrix->translate(10.0f, 0.0f, -10.0f);
	hollowCylinder_modelMatrixTexture = new Mat4();
	hollowCylinder_modelMatrixTexture->scale(2.0f, 2.0f, 2.0f);
	hollowCylinder_modelMatrixTexture->translate(10.0f, 0.0f, -15.0f);

	vertices.clear();
	indices.clear();

	loader->loadGeometry(GeometrySettings{ CONE,16,260.0f,0.0f,0 }, true, true, vertices, indices);
	cone_meshId = renderer_loadMesh(MeshSettings{ false,false,true,true }, vertices.size(), vertices.data(), indices.size(), indices.data());
	cone_color = new Color3f(1.0f, 0.0f, 0.0f);
	cone_modelMatrix = new Mat4();
	cone_modelMatrix->scale(2.0f, 2.0f, 2.0f);
	cone_modelMatrix->translate(-5.0f, 0.0f, -10.0f);
	cone_modelMatrixTexture = new Mat4();
	cone_modelMatrixTexture->scale(2.0f, 2.0f, 2.0f);
	cone_modelMatrixTexture->translate(-5.0f, 0.0f, -15.0f);

	vertices.clear();
	indices.clear();

	loader->loadGeometry(GeometrySettings{ SPHERE,32,260.0f,0.0f,16 }, true, true, vertices, indices);
	sphere_meshId = renderer_loadMesh(MeshSettings{ false,false,true,true }, vertices.size(), vertices.data(), indices.size(), indices.data());
	sphere_color = new Color3f(1.0f, 0.0f, 0.0f);
	sphere_modelMatrix = new Mat4();
	sphere_modelMatrix->scale(2.0f, 2.0f, 2.0f);
	sphere_modelMatrix->translate(-10.0f, 0.0f, -10.0f);
	sphere_modelMatrixTexture = new Mat4();
	sphere_modelMatrixTexture->scale(2.0f, 2.0f, 2.0f);
	sphere_modelMatrixTexture->translate(-10.0f, 0.0f, -15.0f);

	normal_color = new Color3f(1.0f,0.0f,0.0f);*/
}

void Test_GeometryLibrary::update() {
	
}

void Test_GeometryLibrary::doRender() {
	/**Mat4* viewMatrix = new Mat4();
	viewMatrix->setToView(camera);
	renderer_setViewMatrix(viewMatrix->get());

	float colors[] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 1.0f
	};

	renderer_addEntityColor(RenderType::SIMPLE_COLOR_2D, rectangle_modelMatrix->get(), rectangle_meshId, rectangle_color->get());
	renderer_addEntityColor(RenderType::SIMPLE_COLOR_2D, circle_modelMatrix->get(), circle_meshId, circle_color->get());
	renderer_addEntityColor(RenderType::SIMPLE_COLOR_2D, triangle_modelMatrix->get(), triangle_meshId, triangle_color->get());
	renderer_addEntityColor(RenderType::SIMPLE_COLOR_2D, circleRing_modelMatrix->get(), circleRing_meshId, circleRing_color->get());

	//renderer_addEntityColor(RenderType::SIMPLE_COLOR_3D, plane_modelMatrix->get(), plane_meshId, plane_color->get());
	renderer_addEntityGeometry(RenderType::GEOMETRY_3D, GeometrySettings{ CUBE,0,0.0f,0.0f,0 }, cube_modelMatrix->get(), cube_meshId, 6, colors);
	renderer_addEntityGeometry(RenderType::GEOMETRY_3D, GeometrySettings{ CYLINDER,16,260.0f,0.0f,0 }, cylinder_modelMatrix->get(), cylinder_meshId, 6, colors);
	renderer_addEntityGeometry(RenderType::GEOMETRY_3D, GeometrySettings{ HOLLOW_CYLINDER,16,260.0f,0.25f,0 }, hollowCylinder_modelMatrix->get(), hollowCylinder_meshId, 6, colors);
	renderer_addEntityGeometry(RenderType::GEOMETRY_3D, GeometrySettings{ CONE,16,260.0f,0.0f,0 }, cone_modelMatrix->get(), cone_meshId, 6, colors);
	renderer_addEntityGeometry(RenderType::GEOMETRY_3D, GeometrySettings{ SPHERE,32,260.0f,0.0f,16 }, sphere_modelMatrix->get(), sphere_meshId, 6, colors);

	renderer_addEntityTexture(RenderType::SIMPLE_TEXTURE_2D, rectangle_modelMatrixTexture->get(), rectangle_meshId, texture);
	renderer_addEntityTexture(RenderType::SIMPLE_TEXTURE_2D, circle_modelMatrixTexture->get(), circle_meshId, texture);
	renderer_addEntityTexture(RenderType::SIMPLE_TEXTURE_2D, triangle_modelMatrixTexture->get(), triangle_meshId, texture);
	renderer_addEntityTexture(RenderType::SIMPLE_TEXTURE_2D, circleRing_modelMatrixTexture->get(), circleRing_meshId, texture);

	renderer_addEntityTexture(RenderType::SIMPLE_TEXTURE_3D, plane_modelMatrixTexture->get(), plane_meshId, textureFloor);
	renderer_addEntityTexture(RenderType::SIMPLE_TEXTURE_3D, cube_modelMatrixTexture->get(), cube_meshId, texture);
	renderer_addEntityTexture(RenderType::SIMPLE_TEXTURE_3D, cylinder_modelMatrixTexture->get(), cylinder_meshId, texture);
	renderer_addEntityTexture(RenderType::SIMPLE_TEXTURE_3D, hollowCylinder_modelMatrixTexture->get(), hollowCylinder_meshId, texture);
	renderer_addEntityTexture(RenderType::SIMPLE_TEXTURE_3D, cone_modelMatrixTexture->get(), cone_meshId, texture);
	renderer_addEntityTexture(RenderType::SIMPLE_TEXTURE_3D, sphere_modelMatrixTexture->get(), sphere_meshId, texture);

	renderer_addEntityNormal(RenderType::NORMAL, plane_modelMatrixTexture->get(), plane_meshId, normal_color->get());
	renderer_addEntityNormal(RenderType::NORMAL, cube_modelMatrixTexture->get(), cube_meshId, normal_color->get());
	renderer_addEntityNormal(RenderType::NORMAL, cylinder_modelMatrixTexture->get(), cylinder_meshId, normal_color->get());
	renderer_addEntityNormal(RenderType::NORMAL, hollowCylinder_modelMatrixTexture->get(), hollowCylinder_meshId, normal_color->get());
	renderer_addEntityNormal(RenderType::NORMAL, cone_modelMatrixTexture->get(), cone_meshId, normal_color->get());
	renderer_addEntityNormal(RenderType::NORMAL, sphere_modelMatrixTexture->get(), sphere_meshId, normal_color->get());*/
}

void Test_GeometryLibrary::cleanUp() {
	/**loader->unregisterGeometry(RECTANGLE);
	loader->unregisterGeometry(TRIANGLE);
	loader->unregisterGeometry(CIRCLE);
	loader->unregisterGeometry(CIRCLE_RING);

	loader->unregisterGeometry(PLANE);
	loader->unregisterGeometry(CUBE);
	loader->unregisterGeometry(CONE);
	loader->unregisterGeometry(CYLINDER);
	loader->unregisterGeometry(HOLLOW_CYLINDER);
	loader->unregisterGeometry(SPHERE);

	delete loader;*/
}

void Test_GeometryLibrary::setupCamera(){
	camera = new Transform3D();
	camera->getPosition()->setY(2.0f);
}

void Test_GeometryLibrary::loadTextures(){
	int width, height, nrChannels;
	unsigned char* data = stbi_load("C:/Users/tmbal/Desktop/Fierce-Engine/Engine/res/TestTexture.png", &width, &height, &nrChannels, 3);
	texture = renderer_loadTexture(width, height, data);
	unsigned char* data2 = stbi_load("C:/Users/tmbal/Desktop/Fierce-Engine/Engine/res/TestTexture1.png", &width, &height, &nrChannels, 3);
	textureFloor = renderer_loadTexture(width, height, data2);
}

void Test_GeometryLibrary::addActions(){
	inputSystem->addAction(MAPPING::KEY_ESC, new Action_StopEngine(this));
	inputSystem->addAction(MAPPING::MOUSE_AXIS_LR, new Action_LookRightLeft(camera, 0.3f));
	inputSystem->addAction(MAPPING::MOUSE_AXIS_UD, new Action_LookUpDown(camera, 0.3f));
	inputSystem->addAction(MAPPING::KEY_W, new Action_MoveForward(camera, 0.3f));
	inputSystem->addAction(MAPPING::KEY_S, new Action_MoveBackward(camera, 0.3f));
}

void Test_GeometryLibrary::setProjectionMatrices(){
	renderer_setOrthographicProjection((float)window->getWidth(), (float)window->getHeight(), -1.0f, 1.0f);//1920x1080
	renderer_setPerspectiveProjection(((float)window->getWidth()) / ((float)window->getHeight()), 60.0f, 0.1f, 1000.0f);
}