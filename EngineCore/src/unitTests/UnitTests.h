#pragma once

#include "src/core/EngineCore.h"

namespace Fierce {

	class Mat4;
	class Transform2D;
	class Color4f;

	class GeometryLoader;

	class TestWindow : public EngineCore {
	public:
		TestWindow();
		~TestWindow();

		void init() override;
		void update() override;
		void render() override;
		void cleanUp() override;

	private:
		Mat4* m_modelMatrix1=nullptr;
		Mat4* m_modelMatrix2 = nullptr;
		Mat4* m_modelMatrix3 = nullptr;
		Mat4* m_modelMatrix4 = nullptr;
		Mat4* m_projectionMatrix = nullptr;

		int m_meshId_rectangle=0;
		int m_meshId_circle = 0;
		int m_meshId_circleRing = 0;
		int m_meshId_triangle = 0;

		int m_textureId = 0;

		Color4f* m_color = nullptr;
		Color4f* m_color2 = nullptr;
		Color4f* m_color3 = nullptr;
		Color4f* m_color4 = nullptr;

		Transform2D* transform1 = nullptr;
		Transform2D* transform2 = nullptr;
		Transform2D* transform3 = nullptr;
		Transform2D* transform4 = nullptr;

		GeometryLoader* loader = nullptr;
	};

}//end namespace