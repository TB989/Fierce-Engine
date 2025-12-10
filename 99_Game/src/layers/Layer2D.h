#pragma once

#include "src/Bindable.h"
#include "src/Layer.h"
#include "src/math/IColor.h"
#include "src/math/ITransform.h"
#include "src/math/IMatrix.h"

namespace Fierce {
	class Layer2D:public Layer{
	public:
		Layer2D() : Layer("Layer2D") {}

		void OnAttach() override;

		void OnInput(IInputSystem* inputSystem) override;

		void OnUpdate(float dt) override;

		void OnRender(IRenderSystem* renderSystem) override;

		void OnDetach() override;

	private:
		Action* m_action = nullptr;
		Action* m_actionSwitchMouseModeRaw = nullptr;

		int m_meshId_rectangle = 0;
		int m_meshId_circle=0;
		int m_meshId_circleRing = 0;
		int m_meshId_triangle = 0;

		IColor4f* m_color = nullptr;
		IColor4f* m_color2 = nullptr;
		IColor4f* m_color3= nullptr;
		IColor4f* m_color4 = nullptr;
		IColor4f* m_color5 = nullptr;

		ITransform2D* m_transform1 = nullptr;
		ITransform2D* m_transform2 = nullptr;
		ITransform2D* m_transform3 = nullptr;
		ITransform2D* m_transform4 = nullptr;

		IMat4* m_modelMatrix1 = nullptr;
		IMat4* m_modelMatrix2 = nullptr;
		IMat4* m_modelMatrix3 = nullptr;
		IMat4* m_modelMatrix4 = nullptr;

		IMat4* m_orthographicProjectionMatrix = nullptr;
	};
}//end namespace