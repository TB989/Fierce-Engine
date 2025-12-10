#pragma once

#include "src/Bindable.h"
#include "src/Layer.h"
#include "src/math/IColor.h"
#include "src/math/ITransform.h"
#include "src/math/IMatrix.h"

namespace Fierce {
	class Layer3D :public Layer {
	public:
		Layer3D() : Layer("Layer3D") {}

		void OnAttach() override;

		void OnInput(IInputSystem* inputSystem) override;

		void OnUpdate(float dt) override;

		void OnRender(IRenderSystem* renderSystem) override;

		void OnDetach() override;

	private:
		Action* m_action = nullptr;
		Action* m_actionSwitchMouseModeNormal = nullptr;
		State* m_stateMoveForward = nullptr;
		State* m_stateMoveBackward = nullptr;
		Range* m_controlCamera = nullptr;
		Range* m_rangeMoveForward = nullptr;
		Range* m_rangeMoveBackward = nullptr;

		int m_meshId_plane = 0;
		int m_meshId_Cube = 0;
		int m_meshId_Cylinder = 0;
		int m_meshId_HollowCylinder = 0;
		int m_meshId_Cone = 0;
		int m_meshId_Sphere = 0;

		IColor4f* m_color = nullptr;
		IColor4f* m_color2 = nullptr;
		IColor4f* m_color3 = nullptr;
		IColor4f* m_color4 = nullptr;
		IColor4f* m_color5 = nullptr;
		IColor4f* m_colorPlane = nullptr;

		ITransform3D* m_transformPlane = nullptr;
		ITransform3D* m_transformCube = nullptr;
		ITransform3D* m_transformCylinder = nullptr;
		ITransform3D* m_transformHollowCylinder = nullptr;
		ITransform3D* m_transformCone = nullptr;
		ITransform3D* m_transformSphere = nullptr;

		ITransform3D* m_viewTransform = nullptr;

		IMat4* m_modelMatrixPlane = nullptr;
		IMat4* m_modelMatrixCube = nullptr;
		IMat4* m_modelMatrixCylinder = nullptr;
		IMat4* m_modelMatrixHollowCylinder = nullptr;
		IMat4* m_modelMatrixCone = nullptr;
		IMat4* m_modelMatrixSphere = nullptr;

		IMat4* m_perspectiveProjectionMatrix = nullptr;
		IMat4* m_viewMatrix = nullptr;
	};
}//end namespace