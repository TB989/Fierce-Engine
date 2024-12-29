#include "UnitTests.h"

#include <vector>

#include "src/Transform.h"
#include "src/Matrix.h"
#include "src/Vector.h"
#include "src/Color.h"

#include "src/GeometryLoader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "src/io/stb_image.h"

namespace Fierce {

	TestWindow::TestWindow() {
		//m_settings.windowMode = Window::WINDOW_MODE::FULLSCREEN;

		m_loader = new GeometryLoader();
		m_loader->registerGeometry(GeometryType::RECTANGLE,new Rectangle2D());
		m_loader->registerGeometry(GeometryType::CIRCLE, new Circle2D());
		m_loader->registerGeometry(GeometryType::CIRCLE_RING, new CircleRing2D());
		m_loader->registerGeometry(GeometryType::TRIANGLE, new Triangle2D());

		m_loader->registerGeometry(GeometryType::PLANE, new Plane3D());
	}

	TestWindow::~TestWindow() {

	}

	void TestWindow::init() {
		m_action = new Action_StopEngine(this);
		m_inputSystem->addAction(InputSystem::BINDING::KEY_ESC, m_action);
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

		m_logger->info("Loaded meshes");

		//################################################ TEXTURES #####################################################################
		/**int texWidth, texHeight, texChannels;
		stbi_uc* pixels = stbi_load("C:/Users/tmbal/Desktop/Fierce-Engine/VulkanRenderer/res/texture.jpg", &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
		if (!pixels) {
			m_logger->error("Unable to load image.");
		}
		m_textureId = m_renderSystem->newTexture(texWidth,texHeight,4);
		m_renderSystem->textureLoadData(m_textureId, pixels);
		stbi_image_free(pixels);*/

		m_color = new Color4f(1.0f, 0.0f, 0.0f, 1.0f);
		m_color2 = new Color4f(0.0f,1.0f,0.0f,1.0f);
		m_color3 = new Color4f(0.0f, 0.0f, 1.0f, 1.0f);
		m_color4 = new Color4f(1.0f, 1.0f, 0.0f, 1.0f);

		m_colorPlane = new Color4f(1.0f,0.0f,1.0f,1.0f);
		//################################################ Matrices ######################################################################
		m_transform1 = new Transform2D(10.0f,10.0f,100.0f,100.0f,0.0f);
		m_transform2 = new Transform2D(120.0f, 10.0f, 100.0f, 100.0f, 0.0f);
		m_transform3 = new Transform2D(230.0f, 10.0f, 100.0f, 100.0f, 0.0f);
		m_transform4 = new Transform2D(340.0f, 10.0f, 100.0f, 100.0f, 0.0f);

		m_transformPlane = new Transform3D(0.0f,0.0f,0.0f,100.0f,1.0f,100.0f,0.0f,0.0f,0.0f);

		m_modelMatrix1 = new Mat4();
		m_modelMatrix2 = new Mat4();
		m_modelMatrix3 = new Mat4();
		m_modelMatrix4 = new Mat4();

		m_modelMatrixPlane = new Mat4();

		m_orthographicProjectionMatrix = new Mat4();
		m_orthographicProjectionMatrix->setToOrthographicProjection(false, 800.0f,600.0f, 0.0f, 1.0f);
		m_renderSystem->setOrthographicProjection(m_orthographicProjectionMatrix->get());

		m_perspectiveProjectionMatrix = new Mat4();
		m_perspectiveProjectionMatrix->setToPerspectiveProjection(false, 800.0f/600.0f, 60.0f, 0.1f, 1000.0f);
		m_renderSystem->setPerspectiveProjection(m_perspectiveProjectionMatrix->get());

		m_viewTransform = new Transform3D(0.0f,2.0f,0.0f,1.0f,1.0f,1.0f,-5.0f,0.0f,0.0f);
		m_viewMatrix = new Mat4();
		m_viewMatrix->setToView(m_viewTransform);

		m_logger->info("Setup matrices");
	}

	void TestWindow::update() {
		
	}

	void TestWindow::render() {
		//m_logger->info("Start rendering");
		m_renderSystem->startFrame();
		//m_logger->info("After start frame");

		//########### 3D ##########
		m_renderSystem->bindPipeline("Main3D");
		m_renderSystem->setViewMatrix(m_viewMatrix->get());
		//#########################

		//Plane
		m_renderSystem->loadColor(m_colorPlane->get());
		m_modelMatrixPlane->setToTransform(m_transformPlane);
		m_renderSystem->loadModelMatrix(m_modelMatrixPlane->get());
		m_renderSystem->drawMesh(m_meshId_plane);

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

		m_renderSystem->endFrame();
		//m_logger->info("After end frame");
	}

	void TestWindow::cleanUp() {
		delete m_viewMatrix;
		delete m_transform1;
		delete m_transform2;
		delete m_transform3;
		delete m_transform4;
		delete m_transformPlane;
		delete m_modelMatrix1;
		delete m_modelMatrix2;
		delete m_modelMatrix3;
		delete m_modelMatrix4;
		delete m_orthographicProjectionMatrix;
		delete m_perspectiveProjectionMatrix;

		delete m_color;
		delete m_color2;
		delete m_color3;
		delete m_color4;

		m_loader->unregisterGeometry(GeometryType::RECTANGLE);
		m_loader->unregisterGeometry(GeometryType::CIRCLE);
		m_loader->unregisterGeometry(GeometryType::CIRCLE_RING);
		m_loader->unregisterGeometry(GeometryType::TRIANGLE);

		m_loader->unregisterGeometry(GeometryType::PLANE);
		delete m_loader;
	}

}//end namespace