#pragma once

#include "src/core/EngineCore.h"

namespace Fierce {

	class Mat4;
	class Transform2D;

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
		Mat4* m_viewMatrix=nullptr;
		Mat4* m_projectionMatrix = nullptr;

		int m_meshId=0;
		int m_textureId = 0;

		Transform2D* transform1 = nullptr;
		Transform2D* transform2 = nullptr;
	};

}//end namespace