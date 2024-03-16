#include "UnitTests.h"

#include "src/utils/Logging.h"

#include "src/actions/Action_StopEngine.h"
#include "src/actions/Action_LookRightLeft.h"
#include "src/actions/Action_LookUpDown.h"
#include "src/actions/Action_MoveForward.h"
#include "src/actions/Action_MoveBackward.h"

#include "src/system/geometryLoader/GeometryLoaderSystem.h"

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

void Test_GeometryLibrary::loadEntities2D(World* world) {
	ArchetypeId archetypeId;
	Archetype* archetype;

	//####### Colored 2D ###########
	archetypeId = ECS::IdGenerator<GeometrySettings, MeshSettings, Color3f, Transform2D>::getArchetypeId();

	//Colored rectangle
	rectangleColored = world->ecs->createEntity(archetypeId);
	archetype = world->ecs->getOrCreateArchetype(rectangleColored, archetypeId);
	archetype->addComponent(rectangleColored, GeometrySettings{ RECTANGLE,0,0.0f,0.0f,0 });
	archetype->addComponent(rectangleColored, MeshSettings{ true,false,true,false });
	archetype->addComponent(rectangleColored, Color3f(0.0f, 1.0f, 0.0f));
	archetype->addComponent(rectangleColored, Transform2D(10.0f, 10.0f, 100.0f, 100.0f, 0.0f));

	//Colored circle
	circleColored = world->ecs->createEntity(archetypeId);
	archetype = world->ecs->getOrCreateArchetype(circleColored, archetypeId);
	archetype->addComponent(circleColored, GeometrySettings{ CIRCLE,5,360.0f,0.0f,0 });
	archetype->addComponent(circleColored, MeshSettings{ true,false,true,false });
	archetype->addComponent(circleColored, Color3f(1.0f, 0.0f, 0.0f));
	archetype->addComponent(circleColored, Transform2D(120.0f, 10.0f, 100.0f, 100.0f, 0.0f));

	//Colored triangle
	triangleColored = world->ecs->createEntity(archetypeId);
	archetype = world->ecs->getOrCreateArchetype(triangleColored, archetypeId);
	archetype->addComponent(triangleColored, GeometrySettings{ TRIANGLE,0,0.0f,0.0f,0 });
	archetype->addComponent(triangleColored, MeshSettings{ true,false,true,false });
	archetype->addComponent(triangleColored, Color3f(1.0f, 0.0f, 1.0f));
	archetype->addComponent(triangleColored, Transform2D(230.0f, 10.0f, 100.0f, 100.0f, 0.0f));

	//Colored circle ring
	circleRingColored = world->ecs->createEntity(archetypeId);
	archetype = world->ecs->getOrCreateArchetype(circleRingColored, archetypeId);
	archetype->addComponent(circleRingColored, GeometrySettings{ CIRCLE_RING,32,360.0f,0.1f,0 });
	archetype->addComponent(circleRingColored, MeshSettings{ true,false,true,false });
	archetype->addComponent(circleRingColored, Color3f(1.0f, 1.0f, 0.0f));
	archetype->addComponent(circleRingColored, Transform2D(340.0f, 10.0f, 100.0f, 100.0f, 0.0f));

	//####### Textured 2D ###########
	archetypeId = ECS::IdGenerator<GeometrySettings, MeshSettings, Transform2D>::getArchetypeId();

	//Textured rectangle
	rectangleTextured = world->ecs->createEntity(archetypeId);
	archetype = world->ecs->getOrCreateArchetype(rectangleTextured, archetypeId);
	archetype->addComponent(rectangleTextured, GeometrySettings{ RECTANGLE,0,0.0f,0.0f,0 });
	archetype->addComponent(rectangleTextured, MeshSettings{ true,false,true,false });
	archetype->addComponent(rectangleTextured, Transform2D(10.0f, 120.0f, 100.0f, 100.0f, 0.0f));

	//Textured circle
	circleTextured = world->ecs->createEntity(archetypeId);
	archetype = world->ecs->getOrCreateArchetype(circleTextured, archetypeId);
	archetype->addComponent(circleTextured, GeometrySettings{ CIRCLE,5,360.0f,0.0f,0 });
	archetype->addComponent(circleTextured, MeshSettings{ true,false,true,false });
	archetype->addComponent(circleTextured, Transform2D(120.0f, 120.0f, 100.0f, 100.0f, 0.0f));

	//Textured triangle
	triangleTextured = world->ecs->createEntity(archetypeId);
	archetype = world->ecs->getOrCreateArchetype(triangleTextured, archetypeId);
	archetype->addComponent(triangleTextured, GeometrySettings{ TRIANGLE,0,0.0f,0.0f,0 });
	archetype->addComponent(triangleTextured, MeshSettings{ true,false,true,false });
	archetype->addComponent(triangleTextured, Transform2D(230.0f, 120.0f, 100.0f, 100.0f, 0.0f));

	//Textured circle ring
	circleRingTextured = world->ecs->createEntity(archetypeId);
	archetype = world->ecs->getOrCreateArchetype(circleRingTextured, archetypeId);
	archetype->addComponent(circleRingTextured, GeometrySettings{ CIRCLE_RING,32,360.0f,0.1f,0 });
	archetype->addComponent(circleRingTextured, MeshSettings{ true,false,true,false });
	archetype->addComponent(circleRingTextured, Transform2D(340.0f, 120.0f, 100.0f, 100.0f, 0.0f));
}

void Test_GeometryLibrary::loadEntities3D(World* world) {
	ArchetypeId archetypeId;
	Archetype* archetype;

	//####### Colored 3D ###########
	archetypeId = ECS::IdGenerator<GeometrySettings, MeshSettings, Color3f, Transform3D>::getArchetypeId();

	//Colored plane
	planeColored = world->ecs->createEntity(archetypeId);
	archetype = world->ecs->getOrCreateArchetype(planeColored, archetypeId);
	archetype->addComponent(planeColored, GeometrySettings{ PLANE,0,0.0f,0.0f,0 });
	archetype->addComponent(planeColored, MeshSettings{ false,false,true,true });
	archetype->addComponent(planeColored, Color3f(1.0f, 1.0f, 1.0f));
	archetype->addComponent(planeColored, Transform3D(0.0f, -2.0f, 0.0f, 1000.0f, 1.0f, 1000.0f,0.0f, 0.0f, 0.0f));

	//Colored cube
	cubeColored = world->ecs->createEntity(archetypeId);
	archetype = world->ecs->getOrCreateArchetype(cubeColored, archetypeId);
	archetype->addComponent(cubeColored, GeometrySettings{ CUBE,0,0.0f,0.0f,0 });
	archetype->addComponent(cubeColored, MeshSettings{ false,false,true,true });
	archetype->addComponent(cubeColored, Color3f(1.0f, 0.0f, 0.0f));
	archetype->addComponent(cubeColored, Transform3D(0.0f, 0.0f, -10.0f, 2.0f, 2.0f, 2.0f, 0.0f, 0.0f, 0.0f));

	//Colored cylinder
	cylinderColored = world->ecs->createEntity(archetypeId);
	archetype = world->ecs->getOrCreateArchetype(cylinderColored, archetypeId);
	archetype->addComponent(cylinderColored, GeometrySettings{ CYLINDER,16,260.0f,0.0f,0 });
	archetype->addComponent(cylinderColored, MeshSettings{ false,false,true,true });
	archetype->addComponent(cylinderColored, Color3f(1.0f, 0.0f, 0.0f));
	archetype->addComponent(cylinderColored, Transform3D(5.0f, 0.0f, -10.0f, 2.0f, 2.0f, 2.0f, 0.0f, 0.0f, 0.0f));

	//Colored hollow cylinder
	hollowCylinderColored = world->ecs->createEntity(archetypeId);
	archetype = world->ecs->getOrCreateArchetype(hollowCylinderColored, archetypeId);
	archetype->addComponent(hollowCylinderColored, GeometrySettings{ HOLLOW_CYLINDER,16,260.0f,0.1f,0 });
	archetype->addComponent(hollowCylinderColored, MeshSettings{ false,false,true,true });
	archetype->addComponent(hollowCylinderColored, Color3f(1.0f, 0.0f, 0.0f));
	archetype->addComponent(hollowCylinderColored, Transform3D(10.0f, 0.0f, -10.0f, 2.0f, 2.0f, 2.0f, 0.0f, 0.0f, 0.0f));

	//Colored cone
	coneColored = world->ecs->createEntity(archetypeId);
	archetype = world->ecs->getOrCreateArchetype(coneColored, archetypeId);
	archetype->addComponent(coneColored, GeometrySettings{ CONE,16,260.0f,0.0f,0 });
	archetype->addComponent(coneColored, MeshSettings{ false,false,true,true });
	archetype->addComponent(coneColored, Color3f(1.0f, 0.0f, 0.0f));
	archetype->addComponent(coneColored, Transform3D(-5.0f, 0.0f, -10.0f, 2.0f, 2.0f, 2.0f, 0.0f, 0.0f, 0.0f));

	//Colored sphere
	sphereColored = world->ecs->createEntity(archetypeId);
	archetype = world->ecs->getOrCreateArchetype(sphereColored, archetypeId);
	archetype->addComponent(sphereColored, GeometrySettings{ SPHERE,32,260.0f,0.0f,16 });
	archetype->addComponent(sphereColored, MeshSettings{ false,false,true,true });
	archetype->addComponent(sphereColored, Color3f(1.0f, 0.0f, 0.0f));
	archetype->addComponent(sphereColored, Transform3D(-10.0f, 0.0f, -10.0f, 2.0f, 2.0f, 2.0f, 0.0f, 0.0f, 0.0f));

	//####### Textured 3D ###########
	archetypeId = ECS::IdGenerator<GeometrySettings, MeshSettings, Transform3D>::getArchetypeId();

	//Textured plane
	planeTextured = world->ecs->createEntity(archetypeId);
	archetype = world->ecs->getOrCreateArchetype(planeTextured, archetypeId);
	archetype->addComponent(planeTextured, GeometrySettings{ PLANE,0,0.0f,0.0f,0 });
	archetype->addComponent(planeTextured, MeshSettings{ false,false,true,true });
	archetype->addComponent(planeTextured, Transform3D(0.0f, -2.0f, 5.0f, 10.0f, 1.0f, 10.0f, 0.0f, 0.0f, 0.0f));

	//Textured cube
	cubeTextured = world->ecs->createEntity(archetypeId);
	archetype = world->ecs->getOrCreateArchetype(cubeTextured, archetypeId);
	archetype->addComponent(cubeTextured, GeometrySettings{ CUBE,0,0.0f,0.0f,0 });
	archetype->addComponent(cubeTextured, MeshSettings{ false,false,true,true });
	archetype->addComponent(cubeTextured, Transform3D(0.0f, 0.0f, -15.0f, 2.0f, 2.0f, 2.0f, 0.0f, 0.0f, 0.0f));

	//Textured cylinder
	cylinderTextured = world->ecs->createEntity(archetypeId);
	archetype = world->ecs->getOrCreateArchetype(cylinderTextured, archetypeId);
	archetype->addComponent(cylinderTextured, GeometrySettings{ CYLINDER,16,260.0f,0.0f,0 });
	archetype->addComponent(cylinderTextured, MeshSettings{ false,false,true,true });
	archetype->addComponent(cylinderTextured, Transform3D(5.0f, 0.0f, -15.0f, 2.0f, 2.0f, 2.0f, 0.0f, 0.0f, 0.0f));

	//Textured hollow cylinder
	hollowCylinderTextured = world->ecs->createEntity(archetypeId);
	archetype = world->ecs->getOrCreateArchetype(hollowCylinderTextured, archetypeId);
	archetype->addComponent(hollowCylinderTextured, GeometrySettings{ HOLLOW_CYLINDER,16,260.0f,0.1f,0 });
	archetype->addComponent(hollowCylinderTextured, MeshSettings{ false,false,true,true });
	archetype->addComponent(hollowCylinderTextured, Transform3D(10.0f, 0.0f, -15.0f, 2.0f, 2.0f, 2.0f, 0.0f, 0.0f, 0.0f));

	//Textured cone
	coneTextured = world->ecs->createEntity(archetypeId);
	archetype = world->ecs->getOrCreateArchetype(coneTextured, archetypeId);
	archetype->addComponent(coneTextured, GeometrySettings{ CONE,16,260.0f,0.0f,0 });
	archetype->addComponent(coneTextured, MeshSettings{ false,false,true,true });
	archetype->addComponent(coneTextured, Transform3D(-5.0f, 0.0f, -15.0f, 2.0f, 2.0f, 2.0f, 0.0f, 0.0f, 0.0f));

	//Textured sphere
	sphereTextured = world->ecs->createEntity(archetypeId);
	archetype = world->ecs->getOrCreateArchetype(sphereTextured, archetypeId);
	archetype->addComponent(sphereTextured, GeometrySettings{ SPHERE,32,260.0f,0.0f,16 });
	archetype->addComponent(sphereTextured, MeshSettings{ false,false,true,true });
	archetype->addComponent(sphereTextured, Transform3D(-10.0f, 0.0f, -15.0f, 2.0f, 2.0f, 2.0f, 0.0f, 0.0f, 0.0f));
}

void Test_GeometryLibrary::init(World* world) {
	logger = new Logger("MAIN");

	//eventSystem->addListener(this, &Test_GeometryLibrary::onKeyDown);
	//eventSystem->addListener(this, &Test_GeometryLibrary::onMouseMoved);

	loadTextures();

	setupCamera(world);
	setProjectionMatrices(world);
	addActions(world);

	loadEntities2D(world);
	loadEntities3D(world);
	world->loader->process();
	world->ecs->print();

	normal_color = new Color3f(1.0f, 0.0f, 0.0f);
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
	delete logger;
}

void Test_GeometryLibrary::setupCamera(World* world){
	ArchetypeId archetypeId;
	Archetype* archetype;
	archetypeId = ECS::IdGenerator<Transform3D,Camera>::getArchetypeId();

	//Camera
	camera = world->ecs->createEntity(archetypeId);
	archetype = world->ecs->getOrCreateArchetype(camera, archetypeId);
	archetype->addComponent(camera, Transform3D(0.0f, 2.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f));
	archetype->addComponent(camera, Camera((float)window->getWidth(), (float)window->getHeight(),60.0f,-1.0f,1.0f,0.1f,1000.0f));
}

void Test_GeometryLibrary::loadTextures(){
	int width, height, nrChannels;
	unsigned char* data = stbi_load("C:/Users/tmbal/Desktop/Fierce-Engine/Engine/res/TestTexture.png", &width, &height, &nrChannels, 3);
	texture = renderer_loadTexture(width, height, data);
	unsigned char* data2 = stbi_load("C:/Users/tmbal/Desktop/Fierce-Engine/Engine/res/TestTexture1.png", &width, &height, &nrChannels, 3);
	textureFloor = renderer_loadTexture(width, height, data2);
}

void Test_GeometryLibrary::addActions(World* world){
	inputSystem->addAction(MAPPING::KEY_ESC, new Action_StopEngine(this));
	inputSystem->addAction(MAPPING::MOUSE_AXIS_LR, new Action_LookRightLeft(world,camera, 0.3f));
	inputSystem->addAction(MAPPING::MOUSE_AXIS_UD, new Action_LookUpDown(world,camera, 0.3f));
	inputSystem->addAction(MAPPING::KEY_W, new Action_MoveForward(world,camera, 0.3f));
	inputSystem->addAction(MAPPING::KEY_S, new Action_MoveBackward(world,camera, 0.3f));
}

void Test_GeometryLibrary::setProjectionMatrices(World* world){
	Camera* cameraComponent = world->ecs->getComponent<Camera>(camera);

	renderer_setOrthographicProjection(cameraComponent->getWidth(), cameraComponent->getHeight(), cameraComponent->getNearOrtho(), cameraComponent->getFarOrtho());
	renderer_setPerspectiveProjection(cameraComponent->getAspect(), cameraComponent->getFOV(), cameraComponent->getNearPerspective(), cameraComponent->getFarPerspective());
}