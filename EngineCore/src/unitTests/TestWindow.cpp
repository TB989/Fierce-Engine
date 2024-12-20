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

		loader = new GeometryLoader();
		loader->registerGeometry(GeometryType::RECTANGLE,new Rectangle2D());
		loader->registerGeometry(GeometryType::CIRCLE, new Circle2D());
		loader->registerGeometry(GeometryType::CIRCLE_RING, new CircleRing2D());
		loader->registerGeometry(GeometryType::TRIANGLE, new Triangle2D());
	}

	TestWindow::~TestWindow() {

	}

	void TestWindow::init() {
		//###################################### MESHES ###############################################################################
		std::vector<float> vertices;
		std::vector<uint16_t> indices;

		loader->loadGeometry(GeometryType::RECTANGLE,0,0.0f,0.0f,0,vertices, indices);
		m_meshId_rectangle=m_renderSystem->newMesh(vertices.size(),indices.size());
		m_renderSystem->meshLoadVertices(m_meshId_rectangle,vertices.size(),vertices.data());
		m_renderSystem->meshLoadIndices(m_meshId_rectangle, indices.size(), indices.data());

		std::vector<float> vertices2;
		std::vector<uint16_t> indices2;

		loader->loadGeometry(GeometryType::CIRCLE, 32, 250.0f, 0.0f, 0, vertices2, indices2);
		m_meshId_circle = m_renderSystem->newMesh(vertices2.size(), indices2.size());
		m_renderSystem->meshLoadVertices(m_meshId_circle, vertices2.size(), vertices2.data());
		m_renderSystem->meshLoadIndices(m_meshId_circle, indices2.size(), indices2.data());

		std::vector<float> vertices3;
		std::vector<uint16_t> indices3;

		loader->loadGeometry(GeometryType::CIRCLE_RING, 6, 360.0f, 0.25f, 0, vertices3, indices3);
		m_meshId_circleRing = m_renderSystem->newMesh(vertices3.size(), indices3.size());
		m_renderSystem->meshLoadVertices(m_meshId_circleRing, vertices3.size(), vertices3.data());
		m_renderSystem->meshLoadIndices(m_meshId_circleRing, indices3.size(), indices3.data());

		std::vector<float> vertices4;
		std::vector<uint16_t> indices4;

		loader->loadGeometry(GeometryType::TRIANGLE, 0, 0.0f, 0.0f, 0, vertices4, indices4);
		m_meshId_triangle = m_renderSystem->newMesh(vertices4.size(), indices4.size());
		m_renderSystem->meshLoadVertices(m_meshId_triangle, vertices4.size(), vertices4.data());
		m_renderSystem->meshLoadIndices(m_meshId_triangle, indices4.size(), indices4.data());

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
		//################################################ Matrices ######################################################################
		transform1 = new Transform2D(100.0f,75.0f,100.0f,100.0f,0.0f);
		transform2 = new Transform2D(-100.0f, 75.0f, 100.0f, 100.0f, 0.0f);
		transform3 = new Transform2D(100.0f, -75.0f, 100.0f, 100.0f, 0.0f);
		transform4 = new Transform2D(-100.0f, -75.0f, 100.0f, 100.0f, 0.0f);

		m_modelMatrix1 = new Mat4();
		m_modelMatrix2 = new Mat4();
		m_modelMatrix3 = new Mat4();
		m_modelMatrix4 = new Mat4();

		m_projectionMatrix = new Mat4(); 
		m_projectionMatrix->setToOrthographicProjection(false, 800.0f,600.0f, 0.0f, 1.0f);

		m_renderSystem->setOrthographicProjection(m_projectionMatrix->get());

		m_logger->info("Setup matrices");
	}

	void TestWindow::update() {
		float angle1 = transform1->getRotation();
		transform1->setRotation(angle1+0.01f);

		float angle2 = transform2->getRotation();
		transform2->setRotation(angle2 + 0.02f);

		float angle3 = transform3->getRotation();
		transform3->setRotation(angle3 + 0.03f);

		float angle4 = transform4->getRotation();
		transform4->setRotation(angle4 + 0.04f);
	}

	void TestWindow::render() {
		//m_logger->info("Start rendering");
		m_renderSystem->startFrame();
		//m_logger->info("After start frame");

		//Model1
		m_renderSystem->loadColor(m_color->get());
		m_modelMatrix1->setToTransform(transform1);
		m_renderSystem->loadModelMatrix(m_modelMatrix1->get());
		m_renderSystem->drawMesh(m_meshId_rectangle);
		//Model2
		m_renderSystem->loadColor(m_color2->get());
		m_modelMatrix2->setToTransform(transform2);
		m_renderSystem->loadModelMatrix(m_modelMatrix2->get());
		m_renderSystem->drawMesh(m_meshId_circle);
		//Model3
		m_renderSystem->loadColor(m_color3->get());
		m_modelMatrix3->setToTransform(transform3);
		m_renderSystem->loadModelMatrix(m_modelMatrix3->get());
		m_renderSystem->drawMesh(m_meshId_circleRing);
		//Model4
		m_renderSystem->loadColor(m_color4->get());
		m_modelMatrix4->setToTransform(transform4);
		m_renderSystem->loadModelMatrix(m_modelMatrix4->get());
		m_renderSystem->drawMesh(m_meshId_triangle);
		//

		m_renderSystem->endFrame();
		//m_logger->info("After end frame");
	}

	void TestWindow::cleanUp() {
		delete transform1;
		delete transform2;
		delete transform3;
		delete transform4;
		delete m_modelMatrix1;
		delete m_modelMatrix2;
		delete m_modelMatrix3;
		delete m_modelMatrix4;
		delete m_projectionMatrix;

		delete m_color;
		delete m_color2;
		delete m_color3;
		delete m_color4;

		loader->unregisterGeometry(GeometryType::RECTANGLE);
		loader->unregisterGeometry(GeometryType::CIRCLE);
		loader->unregisterGeometry(GeometryType::CIRCLE_RING);
		loader->unregisterGeometry(GeometryType::TRIANGLE);
		delete loader;
	}

}//end namespace