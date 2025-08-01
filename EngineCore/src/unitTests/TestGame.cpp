#include "UnitTests.h"

#include <vector>

#include "src/Transform.h"
#include "src/Matrix.h"
#include "src/Vector.h"
#include "src/Color.h"

#include "src/GeometryLoader.h"

#include "src/Parser_Fnt.h"

#include "src/io/stb_image.h"

#include "src/include/InputSystem.h"

#include "src/utils/Font.h"

namespace Fierce {

	TestGame::TestGame() {
		//m_settings.windowMode = Window::WINDOW_MODE::FULLSCREEN;

		//Parse font
		m_font = new Font();
		std::string fontDirectory = m_settings.assetPath;
		fontDirectory.append("fonts/");
		TextFileReader* reader = m_fileSystem->createTextFileReader(fontDirectory);
		Parser_Fnt* parser = new Parser_Fnt(reader);
		parser->parseFile("Candara.fnt", m_font);
		delete parser;
		m_fileSystem->deleteTextFileReader(reader);

		m_loader = new GeometryLoader();
		m_loader->registerGeometry(GeometryType::RECTANGLE,new Rectangle2D());
		m_loader->registerGeometry(GeometryType::CIRCLE, new Circle2D());
		m_loader->registerGeometry(GeometryType::CIRCLE_RING, new CircleRing2D());
		m_loader->registerGeometry(GeometryType::TRIANGLE, new Triangle2D());

		m_loader->registerGeometry(GeometryType::PLANE, new Plane3D());
		m_loader->registerGeometry(GeometryType::CUBE, new Cube3D());
		m_loader->registerGeometry(GeometryType::CYLINDER, new Cylinder3D());
		m_loader->registerGeometry(GeometryType::HOLLOW_CYLINDER, new HollowCylinder3D());
		m_loader->registerGeometry(GeometryType::CONE, new Cone3D());
		m_loader->registerGeometry(GeometryType::SPHERE, new Sphere3D());
	}

	TestGame::~TestGame() {

	}

	void TestGame::init() {
		//###################################### MESHES ###############################################################################
		std::vector<float> vertices;
		std::vector<uint16_t> indices;

		m_loader->loadGeometry(GeometryType::RECTANGLE,0,0.0f,0.0f,0,vertices, indices);
		m_meshId_rectangle=m_renderSystem->newMesh(vertices.size(),indices.size());
		m_renderSystem->meshLoadVertices(m_meshId_rectangle,vertices.size(),vertices.data());
		m_renderSystem->meshLoadIndices(m_meshId_rectangle, indices.size(), indices.data());

		std::vector<float> vertices2;
		std::vector<uint16_t> indices2;

		m_loader->loadGeometry(GeometryType::CIRCLE, 32, 250.0f, 0.0f, 0, vertices2, indices2);
		m_meshId_circle = m_renderSystem->newMesh(vertices2.size(), indices2.size());
		m_renderSystem->meshLoadVertices(m_meshId_circle, vertices2.size(), vertices2.data());
		m_renderSystem->meshLoadIndices(m_meshId_circle, indices2.size(), indices2.data());

		std::vector<float> vertices3;
		std::vector<uint16_t> indices3;

		m_loader->loadGeometry(GeometryType::CIRCLE_RING, 6, 360.0f, 0.25f, 0, vertices3, indices3);
		m_meshId_circleRing = m_renderSystem->newMesh(vertices3.size(), indices3.size());
		m_renderSystem->meshLoadVertices(m_meshId_circleRing, vertices3.size(), vertices3.data());
		m_renderSystem->meshLoadIndices(m_meshId_circleRing, indices3.size(), indices3.data());

		std::vector<float> vertices4;
		std::vector<uint16_t> indices4;

		m_loader->loadGeometry(GeometryType::TRIANGLE, 0, 0.0f, 0.0f, 0, vertices4, indices4);
		m_meshId_triangle = m_renderSystem->newMesh(vertices4.size(), indices4.size());
		m_renderSystem->meshLoadVertices(m_meshId_triangle, vertices4.size(), vertices4.data());
		m_renderSystem->meshLoadIndices(m_meshId_triangle, indices4.size(), indices4.data());

		std::vector<float> vertices5;
		std::vector<uint16_t> indices5;

		m_loader->loadGeometry(GeometryType::PLANE, 0, 0.0f, 0.0f, 0, vertices5, indices5);
		m_meshId_plane = m_renderSystem->newMesh(vertices5.size(), indices5.size());
		m_renderSystem->meshLoadVertices(m_meshId_plane, vertices5.size(), vertices5.data());
		m_renderSystem->meshLoadIndices(m_meshId_plane, indices5.size(), indices5.data());

		std::vector<float> vertices6;
		std::vector<uint16_t> indices6;

		m_loader->loadGeometry(GeometryType::CUBE, 0, 0.0f, 0.0f, 0, vertices6, indices6);
		m_meshId_Cube = m_renderSystem->newMesh(vertices6.size(), indices6.size());
		m_renderSystem->meshLoadVertices(m_meshId_Cube, vertices6.size(), vertices6.data());
		m_renderSystem->meshLoadIndices(m_meshId_Cube, indices6.size(), indices6.data());

		std::vector<float> vertices7;
		std::vector<uint16_t> indices7;

		m_loader->loadGeometry(GeometryType::CYLINDER, 16, 360.0f, 0.0f, 0, vertices7, indices7);
		m_meshId_Cylinder = m_renderSystem->newMesh(vertices7.size(), indices7.size());
		m_renderSystem->meshLoadVertices(m_meshId_Cylinder, vertices7.size(), vertices7.data());
		m_renderSystem->meshLoadIndices(m_meshId_Cylinder, indices7.size(), indices7.data());

		std::vector<float> vertices8;
		std::vector<uint16_t> indices8;

		m_loader->loadGeometry(GeometryType::HOLLOW_CYLINDER, 16, 360.0f, 0.4f, 0, vertices8, indices8);
		m_meshId_HollowCylinder = m_renderSystem->newMesh(vertices8.size(), indices8.size());
		m_renderSystem->meshLoadVertices(m_meshId_HollowCylinder, vertices8.size(), vertices8.data());
		m_renderSystem->meshLoadIndices(m_meshId_HollowCylinder, indices8.size(), indices8.data());

		std::vector<float> vertices9;
		std::vector<uint16_t> indices9;

		m_loader->loadGeometry(GeometryType::CONE, 16, 360.0f, 0.0f, 0, vertices9, indices9);
		m_meshId_Cone = m_renderSystem->newMesh(vertices9.size(), indices9.size());
		m_renderSystem->meshLoadVertices(m_meshId_Cone, vertices9.size(), vertices9.data());
		m_renderSystem->meshLoadIndices(m_meshId_Cone, indices9.size(), indices9.data());

		std::vector<float> vertices10;
		std::vector<uint16_t> indices10;

		m_loader->loadGeometry(GeometryType::SPHERE, 16, 360.0f, 0.0f, 8, vertices10, indices10);
		m_meshId_Sphere = m_renderSystem->newMesh(vertices10.size(), indices10.size());
		m_renderSystem->meshLoadVertices(m_meshId_Sphere, vertices10.size(), vertices10.data());
		m_renderSystem->meshLoadIndices(m_meshId_Sphere, indices10.size(), indices10.data());


		//Generate mesh for letter
		std::vector<float> vertices11;
		char letter = '?';
		int padding = 0;
		Font::Char character = m_font->chars.chars[letter];
		float x1= (float)(character.x-padding)/(float)m_font->common.scaleW;
		float x2 = (float)(character.x+character.width+padding) / (float)m_font->common.scaleW;
		float y1 = (float)(character.y-padding) / (float)m_font->common.scaleH;
		float y2 = (float)(character.y + character.height+padding) / (float)m_font->common.scaleH;
		vertices11.push_back(0); vertices11.push_back(0); vertices11.push_back(x1); vertices11.push_back(y1);
		vertices11.push_back(0); vertices11.push_back(1); vertices11.push_back(x1); vertices11.push_back(y2);
		vertices11.push_back(1); vertices11.push_back(1); vertices11.push_back(x2); vertices11.push_back(y2);
		vertices11.push_back(1); vertices11.push_back(0); vertices11.push_back(x2); vertices11.push_back(y1);

		std::vector<uint16_t> indices11;
		indices11.push_back(0); indices11.push_back(1); indices11.push_back(2);
		indices11.push_back(0); indices11.push_back(2); indices11.push_back(3);

		m_meshId_Font = m_renderSystem->newMesh(vertices11.size(), indices11.size());
		m_renderSystem->meshLoadVertices(m_meshId_Font, vertices11.size(), vertices11.data());
		m_renderSystem->meshLoadIndices(m_meshId_Font, indices11.size(), indices11.data());

		m_logger->info("Loaded meshes");

		//################################################ TEXTURES #####################################################################
		m_textureId = 0;

		m_color = new Color4f(1.0f, 0.0f, 0.0f, 1.0f);
		m_color2 = new Color4f(0.0f,1.0f,0.0f,1.0f);
		m_color3 = new Color4f(0.0f, 0.0f, 1.0f, 1.0f);
		m_color4 = new Color4f(1.0f, 1.0f, 0.0f, 1.0f);
		m_color5 = new Color4f(0.0f, 1.0f, 1.0f, 1.0f);
		m_color6 = new Color4f(1.0f, 0.0f, 1.0f, 1.0f);
		m_colorFont = new Color4f(1.0f, 1.0f, 1.0f, 1.0f);

		m_colorPlane = new Color4f(1.0f,1.0f,1.0f,1.0f);

		m_logger->info("Loaded colors");

		//################################################ Matrices ######################################################################
		m_transform1 = new Transform2D(10.0f,10.0f,100.0f,100.0f,0.0f);
		m_transform2 = new Transform2D(120.0f, 10.0f, 100.0f, 100.0f, 0.0f);
		m_transform3 = new Transform2D(230.0f, 10.0f, 100.0f, 100.0f, 0.0f);
		m_transform4 = new Transform2D(340.0f, 10.0f, 50.0f, 50.0f, 0.0f);
		m_transform5 = new Transform2D(450.0f, 10.0f, 200.0f, 200.0f, 0.0f);

		m_transformPlane = new Transform3D(0.0f,0.0f,0.0f,100.0f,1.0f,100.0f,0.0f,0.0f,0.0f);
		m_transformCube = new Transform3D(0.0f, 0.5f, 5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f);
		m_transformCylinder = new Transform3D(2.0f, 0.5f, 5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f);
		m_transformHollowCylinder = new Transform3D(-2.0f, 0.5f, 5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f);
		m_transformCone = new Transform3D(4.0f, 0.5f, 5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f);
		m_transformSphere = new Transform3D(-4.0f, 0.5f, 5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f);

		m_modelMatrix1 = new Mat4();
		m_modelMatrix2 = new Mat4();
		m_modelMatrix3 = new Mat4();
		m_modelMatrix4 = new Mat4();
		m_modelMatrix5 = new Mat4();

		m_modelMatrixPlane = new Mat4();
		m_modelMatrixCube = new Mat4();
		m_modelMatrixCylinder = new Mat4();
		m_modelMatrixHollowCylinder = new Mat4();
		m_modelMatrixCone = new Mat4();
		m_modelMatrixSphere = new Mat4();

		m_orthographicProjectionMatrix = new Mat4();
		m_orthographicProjectionMatrix->setToOrthographicProjection(false, 800.0f,600.0f, 0.0f, 1.0f);
		m_renderSystem->setOrthographicProjection(m_orthographicProjectionMatrix->get());

		m_perspectiveProjectionMatrix = new Mat4();
		m_perspectiveProjectionMatrix->setToPerspectiveProjection(false, 800.0f/600.0f, 60.0f, 0.1f, 1000.0f);
		m_renderSystem->setPerspectiveProjection(m_perspectiveProjectionMatrix->get());

		m_viewTransform = new Transform3D(0.0f,2.0f,0.0f,1.0f,1.0f,1.0f,-5.0f,0.0f,0.0f);
		m_viewMatrix = new Mat4();

		m_logger->info("Setup matrices");

		//################################################ Input ######################################################################
		m_player = new Player();

		m_action = new Action_StopEngine(this);
		m_stateMoveForward = new State_MoveForward(m_player);
		m_stateMoveBackward = new State_MoveBackward(m_player);
		m_inputSystem->addAction(BINDING::KEY_ESC, m_action, true);
		m_inputSystem->addAction(BINDING::KEY_ESC, m_action, false);
		m_inputSystem->addState(BINDING::KEY_W, m_stateMoveForward, true);
		m_inputSystem->addState(BINDING::KEY_S, m_stateMoveBackward, true);

		m_actionSwitchMouseModeRaw = new Action_SwitchMouseMode(m_inputSystem, m_window, true);
		m_actionSwitchMouseModeNormal = new Action_SwitchMouseMode(m_inputSystem, m_window, false);
		m_inputSystem->addAction(BINDING::KEY_TAB, m_actionSwitchMouseModeRaw, false);
		m_inputSystem->addAction(BINDING::KEY_TAB, m_actionSwitchMouseModeNormal, true);

		m_lookUpDown = new Range_lookUpDown(m_viewTransform);
		m_inputSystem->addRange(BINDING::MOUSE_Y_AXIS, m_lookUpDown,true);
		m_lookRightLeft = new Range_lookRightLeft(m_viewTransform);
		m_inputSystem->addRange(BINDING::MOUSE_X_AXIS, m_lookRightLeft,true);

		m_rangeMoveForward = new Range_MoveForward(m_viewTransform, m_player,0.02f);
		m_rangeMoveBackward = new Range_MoveBackward(m_viewTransform, m_player,0.02f);

		m_logger->info("Setup input");
	}

	void TestGame::update(double delta){
		//m_logger->info("Timer: %1.3f", delta);
		m_rangeMoveForward->onRangeChanged(delta);
		m_rangeMoveBackward->onRangeChanged(delta);
	}

	void TestGame::render() {
		//m_logger->info("Start rendering");
		//m_renderSystem->startFrame();
		//m_logger->info("After start frame");

		//########### 3D ##########
		m_renderSystem->bindPipeline("Main3D");
		m_viewMatrix->setToView(m_viewTransform);
		m_renderSystem->setViewMatrix(m_viewMatrix->get());
		//#########################

		//Plane
		m_renderSystem->loadColor(m_colorPlane->get());
		m_modelMatrixPlane->setToTransform(m_transformPlane);
		m_renderSystem->loadModelMatrix(m_modelMatrixPlane->get());
		m_renderSystem->drawMesh(m_meshId_plane);

		//Cube
		m_renderSystem->loadColor(m_color->get());
		m_modelMatrixCube->setToTransform(m_transformCube);
		m_renderSystem->loadModelMatrix(m_modelMatrixCube->get());
		m_renderSystem->drawMesh(m_meshId_Cube);

		//Cylinder
		m_renderSystem->loadColor(m_color2->get());
		m_modelMatrixCylinder->setToTransform(m_transformCylinder);
		m_renderSystem->loadModelMatrix(m_modelMatrixCylinder->get());
		m_renderSystem->drawMesh(m_meshId_Cylinder);

		//Hollow Cylinder
		m_renderSystem->loadColor(m_color3->get());
		m_modelMatrixHollowCylinder->setToTransform(m_transformHollowCylinder);
		m_renderSystem->loadModelMatrix(m_modelMatrixHollowCylinder->get());
		m_renderSystem->drawMesh(m_meshId_HollowCylinder);

		//Cone
		m_renderSystem->loadColor(m_color4->get());
		m_modelMatrixCone->setToTransform(m_transformCone);
		m_renderSystem->loadModelMatrix(m_modelMatrixCone->get());
		m_renderSystem->drawMesh(m_meshId_Cone);

		//Sphere
		m_renderSystem->loadColor(m_color5->get());
		m_modelMatrixSphere->setToTransform(m_transformSphere);
		m_renderSystem->loadModelMatrix(m_modelMatrixSphere->get());
		m_renderSystem->drawMesh(m_meshId_Sphere);

		//########### 2D ##########
		m_renderSystem->bindPipeline("Main");
		//#########################

		//Model1
		m_renderSystem->loadColor(m_color->get());
		m_modelMatrix1->setToTransform(m_transform1);
		m_renderSystem->loadModelMatrix(m_modelMatrix1->get());
		m_renderSystem->drawMesh(m_meshId_rectangle);
		//Model2
		m_renderSystem->loadColor(m_color2->get());
		m_modelMatrix2->setToTransform(m_transform2);
		m_renderSystem->loadModelMatrix(m_modelMatrix2->get());
		m_renderSystem->drawMesh(m_meshId_circle);
		//Model3
		m_renderSystem->loadColor(m_color3->get());
		m_modelMatrix3->setToTransform(m_transform3);
		m_renderSystem->loadModelMatrix(m_modelMatrix3->get());
		m_renderSystem->drawMesh(m_meshId_circleRing);
		//Model4
		m_renderSystem->loadColor(m_color4->get());
		m_modelMatrix4->setToTransform(m_transform4);
		m_renderSystem->loadModelMatrix(m_modelMatrix4->get());
		m_renderSystem->drawMesh(m_meshId_triangle);
		//

		//########### Font ########
		m_renderSystem->bindPipeline("Font");
		//#########################

		m_renderSystem->loadColor(m_colorFont->get());
		m_modelMatrix5->setToTransform(m_transform5);
		m_renderSystem->loadModelMatrix(m_modelMatrix5->get());
		m_renderSystem->activateSampler("Font", m_textureId);
		m_renderSystem->drawMesh(m_meshId_Font);

		//m_renderSystem->endFrame();
		//m_logger->info("After end frame");
	}

	void TestGame::renderGUI(GraphicsContext* context){
		m_renderSystem->bindPipeline("GUI");
		//context->setColor(255,0,0);
		//context->drawRect(500,200,100,100);
		//context->setColor(188, 47, 86);
		//context->drawRect(200, 200, 500, 100);

		m_renderSystem->drawGraphicsContext();
	}

	void TestGame::cleanUp() {
		delete m_transform1;
		delete m_transform2;
		delete m_transform3;
		delete m_transform4;
		delete m_transform5;
		delete m_transformPlane;
		delete m_transformCube;
		delete m_transformCylinder;
		delete m_transformHollowCylinder;
		delete m_transformCone;
		delete m_transformSphere;

		delete m_modelMatrix1;
		delete m_modelMatrix2;
		delete m_modelMatrix3;
		delete m_modelMatrix4;
		delete m_modelMatrix5;
		delete m_modelMatrixPlane;
		delete m_modelMatrixCube;
		delete m_modelMatrixCylinder;
		delete m_modelMatrixHollowCylinder;
		delete m_modelMatrixCone;
		delete m_modelMatrixSphere;
		delete m_orthographicProjectionMatrix;
		delete m_perspectiveProjectionMatrix;
		delete m_viewMatrix;

		delete m_color;
		delete m_color2;
		delete m_color3;
		delete m_color4;
		delete m_color5;
		delete m_color6;
		delete m_colorPlane;

		m_loader->unregisterGeometry(GeometryType::RECTANGLE);
		m_loader->unregisterGeometry(GeometryType::CIRCLE);
		m_loader->unregisterGeometry(GeometryType::CIRCLE_RING);
		m_loader->unregisterGeometry(GeometryType::TRIANGLE);

		m_loader->unregisterGeometry(GeometryType::PLANE);
		m_loader->unregisterGeometry(GeometryType::CUBE);
		m_loader->unregisterGeometry(GeometryType::CYLINDER);
		m_loader->unregisterGeometry(GeometryType::HOLLOW_CYLINDER);
		m_loader->unregisterGeometry(GeometryType::CONE);
		m_loader->unregisterGeometry(GeometryType::SPHERE);
		delete m_loader;
	}

}//end namespace