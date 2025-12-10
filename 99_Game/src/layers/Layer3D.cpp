#include "Layer3D.h"

#include "src/input/Action_StopEngine.h"
#include "src/input/State_MoveForward.h"
#include "src/input/State_MoveBackward.h"
#include "src/input/Range_MoveForward.h"
#include "src/input/Range_MoveBackward.h"
#include "src/input/Range_controlCamera.h"
#include "src/input/Action_SwitchMouseMode.h"

#include "src/systems/IGeometrySystem.h"
#include "src/systems/IRenderSystem.h"
#include "src/systems/IWindowSystem.h"
#include "src/systems/IMathSystem.h"

#include <vector>

namespace Fierce {
	void Layer3D::OnAttach(){
		IGeometrySystem* geometrySystem = nullptr;
		IRenderSystem* renderSystem = nullptr;
		IMathSystem* mathSystem = nullptr;
		IWindow* m_window = nullptr;

		//###################################### Meshes ###############################################################################
		std::vector<float> vertices5;
		std::vector<uint16_t> indices5;

		geometrySystem->loadGeometry(GeometryType::PLANE, 0, 0.0f, 0.0f, 0, vertices5, indices5);
		m_meshId_plane = renderSystem->newMesh(vertices5.size(), indices5.size());
		renderSystem->meshLoadVertices(m_meshId_plane, vertices5.size(), vertices5.data());
		renderSystem->meshLoadIndices(m_meshId_plane, indices5.size(), indices5.data());

		std::vector<float> vertices6;
		std::vector<uint16_t> indices6;

		geometrySystem->loadGeometry(GeometryType::CUBE, 0, 0.0f, 0.0f, 0, vertices6, indices6);
		m_meshId_Cube = renderSystem->newMesh(vertices6.size(), indices6.size());
		renderSystem->meshLoadVertices(m_meshId_Cube, vertices6.size(), vertices6.data());
		renderSystem->meshLoadIndices(m_meshId_Cube, indices6.size(), indices6.data());

		std::vector<float> vertices7;
		std::vector<uint16_t> indices7;

		geometrySystem->loadGeometry(GeometryType::CYLINDER, 16, 360.0f, 0.0f, 0, vertices7, indices7);
		m_meshId_Cylinder = renderSystem->newMesh(vertices7.size(), indices7.size());
		renderSystem->meshLoadVertices(m_meshId_Cylinder, vertices7.size(), vertices7.data());
		renderSystem->meshLoadIndices(m_meshId_Cylinder, indices7.size(), indices7.data());

		std::vector<float> vertices8;
		std::vector<uint16_t> indices8;

		geometrySystem->loadGeometry(GeometryType::HOLLOW_CYLINDER, 16, 360.0f, 0.4f, 0, vertices8, indices8);
		m_meshId_HollowCylinder = renderSystem->newMesh(vertices8.size(), indices8.size());
		renderSystem->meshLoadVertices(m_meshId_HollowCylinder, vertices8.size(), vertices8.data());
		renderSystem->meshLoadIndices(m_meshId_HollowCylinder, indices8.size(), indices8.data());

		std::vector<float> vertices9;
		std::vector<uint16_t> indices9;

		geometrySystem->loadGeometry(GeometryType::CONE, 16, 360.0f, 0.0f, 0, vertices9, indices9);
		m_meshId_Cone = renderSystem->newMesh(vertices9.size(), indices9.size());
		renderSystem->meshLoadVertices(m_meshId_Cone, vertices9.size(), vertices9.data());
		renderSystem->meshLoadIndices(m_meshId_Cone, indices9.size(), indices9.data());

		std::vector<float> vertices10;
		std::vector<uint16_t> indices10;

		geometrySystem->loadGeometry(GeometryType::SPHERE, 16, 360.0f, 0.0f, 8, vertices10, indices10);
		m_meshId_Sphere = renderSystem->newMesh(vertices10.size(), indices10.size());
		renderSystem->meshLoadVertices(m_meshId_Sphere, vertices10.size(), vertices10.data());
		renderSystem->meshLoadIndices(m_meshId_Sphere, indices10.size(), indices10.data());

		//################################################ Colors #####################################################################
		m_color = mathSystem->createColor(1.0f, 0.0f, 0.0f, 1.0f);
		m_color2 = mathSystem->createColor(0.0f, 1.0f, 0.0f, 1.0f);
		m_color3 = mathSystem->createColor(0.0f, 0.0f, 1.0f, 1.0f);
		m_color4 = mathSystem->createColor(1.0f, 1.0f, 0.0f, 1.0f);
		m_color5 = mathSystem->createColor(0.0f, 1.0f, 1.0f, 1.0f);

		m_colorPlane = mathSystem->createColor(1.0f, 1.0f, 1.0f, 1.0f);

		//################################################ Trafos ######################################################################
		m_transformPlane = mathSystem->createTransform3D(0.0f, 0.0f, 0.0f, 100.0f, 1.0f, 100.0f, 0.0f, 0.0f, 0.0f);
		m_transformCube = mathSystem->createTransform3D(0.0f, 0.5f, 5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f);
		m_transformCylinder = mathSystem->createTransform3D(2.0f, 0.5f, 5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f);
		m_transformHollowCylinder = mathSystem->createTransform3D(-2.0f, 0.5f, 5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f);
		m_transformCone = mathSystem->createTransform3D(4.0f, 0.5f, 5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f);
		m_transformSphere = mathSystem->createTransform3D(-4.0f, 0.5f, 5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f);

		//################################################ Matrices ######################################################################
		m_modelMatrixPlane = mathSystem->createMatrix();
		m_modelMatrixCube = mathSystem->createMatrix();
		m_modelMatrixCylinder = mathSystem->createMatrix();
		m_modelMatrixHollowCylinder = mathSystem->createMatrix();
		m_modelMatrixCone = mathSystem->createMatrix();
		m_modelMatrixSphere = mathSystem->createMatrix();

		//################################################ Projection and view matrix ######################################################################
		m_perspectiveProjectionMatrix = mathSystem->createMatrix();
		m_perspectiveProjectionMatrix->setToPerspectiveProjection(false, (float)m_window->getWidth() / (float)m_window->getHeight(), 60.0f, 0.1f, 1000.0f);
		renderSystem->setPerspectiveProjection(m_perspectiveProjectionMatrix->get());

		m_viewTransform = mathSystem->createTransform3D(0.0f, 2.0f, 0.0f, 1.0f, 1.0f, 1.0f, -5.0f, 0.0f, 0.0f);
		m_viewMatrix = mathSystem->createMatrix();
	}

	void Layer3D::OnInput(IInputSystem* inputSystem){
		IWindow* m_window = nullptr;
		Player* m_player = nullptr;

		//m_action = new Action_StopEngine(this);
		m_stateMoveForward = new State_MoveForward(m_player);
		m_stateMoveBackward = new State_MoveBackward(m_player);
		m_actionSwitchMouseModeNormal = new Action_SwitchMouseMode(inputSystem, m_window, false);
		m_controlCamera = new Range_controlCamera(m_viewTransform);
		m_rangeMoveForward = new Range_MoveForward(m_viewTransform, m_player, 0.02f);
		m_rangeMoveBackward = new Range_MoveBackward(m_viewTransform, m_player, 0.02f);

		//inputSystem->addAction(BINDING::KEY_ESC, m_action, true);
		inputSystem->addState(BINDING::KEY_W, m_stateMoveForward, true);
		inputSystem->addState(BINDING::KEY_S, m_stateMoveBackward, true);
		inputSystem->addAction(BINDING::KEY_TAB, m_actionSwitchMouseModeNormal, true);
		inputSystem->addRange(BINDING::MOUSE_MOVE, m_controlCamera, true);
	}

	void Layer3D::OnUpdate(float dt){
		m_rangeMoveForward->onRangeChanged(dt, 0.0f);
		m_rangeMoveBackward->onRangeChanged(dt, 0.0f);
	}

	void Layer3D::OnRender(IRenderSystem* renderSystem){
		renderSystem->bindPipeline("Main3D");
		m_viewMatrix->setToView(m_viewTransform);
		renderSystem->setViewMatrix(m_viewMatrix->get());

		//Plane
		renderSystem->loadColor(m_colorPlane->get());
		m_modelMatrixPlane->setToTransform(m_transformPlane);
		renderSystem->loadModelMatrix(m_modelMatrixPlane->get());
		renderSystem->drawMesh(m_meshId_plane);

		//Cube
		renderSystem->loadColor(m_color->get());
		m_modelMatrixCube->setToTransform(m_transformCube);
		renderSystem->loadModelMatrix(m_modelMatrixCube->get());
		renderSystem->drawMesh(m_meshId_Cube);

		//Cylinder
		renderSystem->loadColor(m_color2->get());
		m_modelMatrixCylinder->setToTransform(m_transformCylinder);
		renderSystem->loadModelMatrix(m_modelMatrixCylinder->get());
		renderSystem->drawMesh(m_meshId_Cylinder);

		//Hollow Cylinder
		renderSystem->loadColor(m_color3->get());
		m_modelMatrixHollowCylinder->setToTransform(m_transformHollowCylinder);
		renderSystem->loadModelMatrix(m_modelMatrixHollowCylinder->get());
		renderSystem->drawMesh(m_meshId_HollowCylinder);

		//Cone
		renderSystem->loadColor(m_color4->get());
		m_modelMatrixCone->setToTransform(m_transformCone);
		renderSystem->loadModelMatrix(m_modelMatrixCone->get());
		renderSystem->drawMesh(m_meshId_Cone);

		//Sphere
		renderSystem->loadColor(m_color5->get());
		m_modelMatrixSphere->setToTransform(m_transformSphere);
		renderSystem->loadModelMatrix(m_modelMatrixSphere->get());
		renderSystem->drawMesh(m_meshId_Sphere);
	}

	void Layer3D::OnDetach(){
		delete m_transformPlane;
		delete m_transformCube;
		delete m_transformCylinder;
		delete m_transformHollowCylinder;
		delete m_transformCone;
		delete m_transformSphere;

		delete m_modelMatrixPlane;
		delete m_modelMatrixCube;
		delete m_modelMatrixCylinder;
		delete m_modelMatrixHollowCylinder;
		delete m_modelMatrixCone;
		delete m_modelMatrixSphere;

		delete m_perspectiveProjectionMatrix;
		delete m_viewMatrix;

		delete m_color;
		delete m_color2;
		delete m_color3;
		delete m_color4;
		delete m_color5;
		delete m_colorPlane;
	}
}//end namespace