#pragma once

#include "src/Common.h"

#include "src/core/Core.h"

#include "GeometryLibrary.h"
#include "MathLibrary.h"
#include "src/camera/Camera.h"

#include "Logger.h"

class Test_EngineConfig : public Core {
public:
	Test_EngineConfig();

protected:
	void init(World* world) override;
	void update() override;
	void doRender() override;
	void cleanUp() override;
};

class Test_GeometryLibrary : public Core {
public:
	Test_GeometryLibrary();

	//void onMouseMoved(MouseMoveEvent* event);
	//void onKeyDown(KeyDownEvent* event);

protected:
	void init(World* world) override;
	void update() override;
	void doRender() override;
	void cleanUp() override;

private:
	void setupCamera(World* world);
	void loadTextures();
	void addActions(World* world);
	void setProjectionMatrices(World* world);
	void loadEntities2D(World* world);
	void loadEntities3D(World* world);

private:
	Logger* logger;

	int m_x_alt=0;
	int m_y_alt = 0;
	bool first=true;

	int texture;
	int textureFloor;

	Color3f* normal_color;

	EntityId camera;

	EntityId rectangleColored;
	EntityId circleColored;
	EntityId triangleColored;
	EntityId circleRingColored;

	EntityId rectangleTextured;
	EntityId circleTextured;
	EntityId triangleTextured;
	EntityId circleRingTextured;

	EntityId planeColored;
	EntityId cubeColored;
	EntityId cylinderColored;
	EntityId hollowCylinderColored;
	EntityId coneColored;
	EntityId sphereColored;

	EntityId planeTextured;
	EntityId cubeTextured;
	EntityId cylinderTextured;
	EntityId hollowCylinderTextured;
	EntityId coneTextured;
	EntityId sphereTextured;
};