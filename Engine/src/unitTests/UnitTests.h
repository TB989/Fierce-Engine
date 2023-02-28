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

protected:
	void init() override;
	void update() override;
	void doRender() override;
	void cleanUp() override;

private:
	int rectangle_meshId;
	int circle_meshId;
	int triangle_meshId;
	int circleRing_meshId;
	int plane_meshId;

	Mat4* rectangle_modelMatrix;
	Mat4* circle_modelMatrix;
	Mat4* triangle_modelMatrix;
	Mat4* circleRing_modelMatrix;
	Mat4* plane_modelMatrix;

	Color3f* rectangle_color;
	Color3f* circle_color;
	Color3f* triangle_color;
	Color3f* circleRing_color;
	Color3f* plane_color;

	GeometryLoader* loader;
};