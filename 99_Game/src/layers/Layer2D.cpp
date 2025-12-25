#include "Layer2D.h"

#include "src/input/Action_StopEngine.h"
#include "src/input/Action_SwitchMouseMode.h"

#include "src/systems/IGeometrySystem.h"
#include "src/systems/IRenderSystem.h"
#include "src/systems/IWindowSystem.h"
#include "src/systems/IMathSystem.h"

#include <vector>

namespace Fierce {
    void Layer2D::OnAttach(ISystemManager* manager){
		IGeometrySystem* geometrySystem = (IGeometrySystem*)manager->getSystem("GeometrySystem");
		IRenderSystem* renderSystem = (IRenderSystem*)manager->getSystem("RenderSystem");
		IMathSystem* mathSystem = (IMathSystem*)manager->getSystem("MathSystem");
		IWindow* m_window=nullptr;

		//###################################### Meshes ###############################################################################
		std::vector<float> vertices;
		std::vector<uint16_t> indices;

		geometrySystem->loadGeometry(GeometryType::RECTANGLE, 0, 0.0f, 0.0f, 0, vertices, indices);
		m_meshId_rectangle = renderSystem->newMesh(vertices.size(), indices.size());
		renderSystem->meshLoadVertices(m_meshId_rectangle, vertices.size(), vertices.data());
		renderSystem->meshLoadIndices(m_meshId_rectangle, indices.size(), indices.data());

		std::vector<float> vertices2;
		std::vector<uint16_t> indices2;

		geometrySystem->loadGeometry(GeometryType::CIRCLE, 32, 250.0f, 0.0f, 0, vertices2, indices2);
		m_meshId_circle = renderSystem->newMesh(vertices2.size(), indices2.size());
		renderSystem->meshLoadVertices(m_meshId_circle, vertices2.size(), vertices2.data());
		renderSystem->meshLoadIndices(m_meshId_circle, indices2.size(), indices2.data());

		std::vector<float> vertices3;
		std::vector<uint16_t> indices3;

		geometrySystem->loadGeometry(GeometryType::CIRCLE_RING, 6, 360.0f, 0.25f, 0, vertices3, indices3);
		m_meshId_circleRing = renderSystem->newMesh(vertices3.size(), indices3.size());
		renderSystem->meshLoadVertices(m_meshId_circleRing, vertices3.size(), vertices3.data());
		renderSystem->meshLoadIndices(m_meshId_circleRing, indices3.size(), indices3.data());

		std::vector<float> vertices4;
		std::vector<uint16_t> indices4;

		geometrySystem->loadGeometry(GeometryType::TRIANGLE, 0, 0.0f, 0.0f, 0, vertices4, indices4);
		m_meshId_triangle = renderSystem->newMesh(vertices4.size(), indices4.size());
		renderSystem->meshLoadVertices(m_meshId_triangle, vertices4.size(), vertices4.data());
		renderSystem->meshLoadIndices(m_meshId_triangle, indices4.size(), indices4.data());

		//################################################ Colors #####################################################################
		m_color = mathSystem->createColor(1.0f, 0.0f, 0.0f, 1.0f);
		m_color2 = mathSystem->createColor(0.0f, 1.0f, 0.0f, 1.0f);
		m_color3 = mathSystem->createColor(0.0f, 0.0f, 1.0f, 1.0f);
		m_color4 = mathSystem->createColor(1.0f, 1.0f, 0.0f, 1.0f);
		m_color5 = mathSystem->createColor(0.0f, 1.0f, 1.0f, 1.0f);

		//################################################ Trafos ######################################################################
		m_transform1 = mathSystem->createTransform2D(10.0f, 10.0f, 100.0f, 100.0f, 0.0f);
		m_transform2 = mathSystem->createTransform2D(120.0f, 10.0f, 100.0f, 100.0f, 0.0f);
		m_transform3 = mathSystem->createTransform2D(230.0f, 10.0f, 100.0f, 100.0f, 0.0f);
		m_transform4 = mathSystem->createTransform2D(340.0f, 10.0f, 50.0f, 50.0f, 0.0f);

		//################################################ Matrices ######################################################################
		m_modelMatrix1 = mathSystem->createMatrix();
		m_modelMatrix2 = mathSystem->createMatrix();
		m_modelMatrix3 = mathSystem->createMatrix();
		m_modelMatrix4 = mathSystem->createMatrix();

		//################################################ Projection matrix ######################################################################
		m_orthographicProjectionMatrix = mathSystem->createMatrix();
		m_orthographicProjectionMatrix->setToOrthographicProjection(false, m_window->getWidth(), m_window->getHeight(), 0.0f, 1.0f);
		renderSystem->setOrthographicProjection(m_orthographicProjectionMatrix->get());
    }

	void Layer2D::OnInput(IInputSystem* inputSystem){
		IWindow* m_window = nullptr;

		//m_action = new Action_StopEngine(this);
		m_actionSwitchMouseModeRaw = new Action_SwitchMouseMode(inputSystem, m_window, true);

		//inputSystem->addAction(BINDING::KEY_ESC, m_action, false);
		inputSystem->addAction(BINDING::KEY_TAB, m_actionSwitchMouseModeRaw, false);
	}

    void Layer2D::OnUpdate(float dt){

    }

    void Layer2D::OnRender(IRenderSystem* renderSystem){
		renderSystem->bindPipeline("Main");

		//Model1
		renderSystem->loadColor(m_color->get());
		m_modelMatrix1->setToTransform(m_transform1);
		renderSystem->loadModelMatrix(m_modelMatrix1->get());
		renderSystem->drawMesh(m_meshId_rectangle);

		//Model2
		renderSystem->loadColor(m_color2->get());
		m_modelMatrix2->setToTransform(m_transform2);
		renderSystem->loadModelMatrix(m_modelMatrix2->get());
		renderSystem->drawMesh(m_meshId_circle);

		//Model3
		renderSystem->loadColor(m_color3->get());
		m_modelMatrix3->setToTransform(m_transform3);
		renderSystem->loadModelMatrix(m_modelMatrix3->get());
		renderSystem->drawMesh(m_meshId_circleRing);

		//Model4
		renderSystem->loadColor(m_color4->get());
		m_modelMatrix4->setToTransform(m_transform4);
		renderSystem->loadModelMatrix(m_modelMatrix4->get());
		renderSystem->drawMesh(m_meshId_triangle);
    }

	void Layer2D::OnDetach(ISystemManager* manager){
		delete m_transform1;
		delete m_transform2;
		delete m_transform3;
		delete m_transform4;

		delete m_modelMatrix1;
		delete m_modelMatrix2;
		delete m_modelMatrix3;
		delete m_modelMatrix4;

		delete m_orthographicProjectionMatrix;

		delete m_color;
		delete m_color2;
		delete m_color3;
		delete m_color4;
		delete m_color5;
	}
}//end namespace