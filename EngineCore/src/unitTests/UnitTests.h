#pragma once

#include "src/core/EngineCore.h"

#include "src/actions/Action_StopEngine.h"
#include "src/actions/State_MoveForward.h"
#include "src/actions/State_MoveBackward.h"
#include "src/actions/Range_MoveForward.h"
#include "src/actions/Range_MoveBackward.h"
#include "src/actions/Range_lookUpDown.h"
#include "src/actions/Range_lookRightLeft.h"
#include "src/actions/Action_SwitchMouseMode.h"

#include "src/gameplay/Player.h"

namespace Fierce {

	class Font;

	class Mat4;
	class Transform2D;
	class Transform3D;
	class Color4f;

	class GeometryLoader;

	class TestGame : public EngineCore {
	public:
		TestGame();
		~TestGame();

		void init() override;
		void update(double delta) override;
		void render() override;
		void renderGUI(GraphicsContext* context) override;
		void cleanUp() override;

	private:
		Player* m_player = nullptr;

		Action* m_action = nullptr;
		Action* m_actionSwitchMouseModeRaw = nullptr;
		Action* m_actionSwitchMouseModeNormal = nullptr;
		State* m_stateMoveForward=nullptr;
		State* m_stateMoveBackward = nullptr;
		Range* m_lookUpDown = nullptr;
		Range* m_lookRightLeft = nullptr;
		Range* m_rangeMoveForward = nullptr;
		Range* m_rangeMoveBackward = nullptr;

		Mat4* m_modelMatrix1=nullptr;
		Mat4* m_modelMatrix2 = nullptr;
		Mat4* m_modelMatrix3 = nullptr;
		Mat4* m_modelMatrix4 = nullptr;

		Mat4* m_modelMatrixPlane = nullptr;
		Mat4* m_modelMatrixCube = nullptr;
		Mat4* m_modelMatrixCylinder = nullptr;
		Mat4* m_modelMatrixHollowCylinder = nullptr;
		Mat4* m_modelMatrixCone = nullptr;
		Mat4* m_modelMatrixSphere = nullptr;
		Mat4* m_orthographicProjectionMatrix = nullptr;
		Mat4* m_perspectiveProjectionMatrix = nullptr;
		Mat4* m_viewMatrix=nullptr;

		int m_meshId_rectangle=0;
		int m_meshId_circle = 0;
		int m_meshId_circleRing = 0;
		int m_meshId_triangle = 0;

		int m_meshId_plane = 0;
		int m_meshId_Cube = 0;
		int m_meshId_Cylinder = 0;
		int m_meshId_HollowCylinder = 0;
		int m_meshId_Cone = 0;
		int m_meshId_Sphere = 0;

		int m_meshId_Font = 0;

		int m_textureId = 0;

		Color4f* m_color = nullptr;
		Color4f* m_color2 = nullptr;
		Color4f* m_color3 = nullptr;
		Color4f* m_color4 = nullptr;
		Color4f* m_color5 = nullptr;

		Color4f* m_colorFont = nullptr;

		Color4f* m_colorPlane = nullptr;

		Transform3D* m_viewTransform=nullptr;
		Transform2D* m_transform1 = nullptr;
		Transform2D* m_transform2 = nullptr;
		Transform2D* m_transform3 = nullptr;
		Transform2D* m_transform4 = nullptr;

		Transform3D* m_transformPlane = nullptr;
		Transform3D* m_transformCube = nullptr;
		Transform3D* m_transformCylinder = nullptr;
		Transform3D* m_transformHollowCylinder = nullptr;
		Transform3D* m_transformCone = nullptr;
		Transform3D* m_transformSphere = nullptr;

		GeometryLoader* m_loader = nullptr;
	};

	class TestGUI : public EngineCore {
	public:
		TestGUI();
		~TestGUI();

		void init() override;
		void update(double delta) override;
		void render() override;
		void renderGUI(GraphicsContext* context) override;
		void cleanUp() override;

	private:
		Action* m_action = nullptr;
		Mat4* m_orthographicProjectionMatrix = nullptr;
		Mat4* m_perspectiveProjectionMatrix = nullptr;
	};

}//end namespace