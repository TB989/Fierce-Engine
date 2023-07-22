#pragma once

#include "src/Common.h"

#include "src/core/Core.h"

#include "GeometryLibrary.h"
#include "MathLibrary.h"

class Test_EngineConfig : public Core {
public:
	Test_EngineConfig();

protected:
	void init() override;
	void update() override;
	void doRender() override;
	void cleanUp() override;
};

class Test_GeometryLibrary : public Core {
public:
	Test_GeometryLibrary();

	void onMouseMoved(MouseMoveEvent* event);
	void onKeyDown(KeyDownEvent* event);

protected:
	void init() override;
	void update() override;
	void doRender() override;
	void cleanUp() override;

private:
	int m_x_alt=0;
	int m_y_alt = 0;
	bool first=true;
	Transform3D* camera;

	int rectangle_meshId;
	int circle_meshId;
	int triangle_meshId;
	int circleRing_meshId;

	int plane_meshId;
	int cube_meshId;
	int cylinder_meshId;
	int hollowCylinder_meshId;
	int cone_meshId;
	int sphere_meshId;

	int texture;

	Mat4* rectangle_modelMatrix;
	Mat4* rectangle_modelMatrixTexture;
	Mat4* circle_modelMatrix;
	Mat4* circle_modelMatrixTexture;
	Mat4* triangle_modelMatrix;
	Mat4* triangle_modelMatrixTexture;
	Mat4* circleRing_modelMatrix;
	Mat4* circleRing_modelMatrixTexture;

	Mat4* plane_modelMatrix;
	Mat4* cube_modelMatrix;
	Mat4* cylinder_modelMatrix;
	Mat4* hollowCylinder_modelMatrix;
	Mat4* cone_modelMatrix;
	Mat4* sphere_modelMatrix;

	Color3f* rectangle_color;
	Color3f* circle_color;
	Color3f* triangle_color;
	Color3f* circleRing_color;

	Color3f* plane_color;
	Color3f* cube_color;
	Color3f* cylinder_color;
	Color3f* hollowCylinder_color;
	Color3f* cone_color;
	Color3f* sphere_color;

	GeometryLoader* loader;
};