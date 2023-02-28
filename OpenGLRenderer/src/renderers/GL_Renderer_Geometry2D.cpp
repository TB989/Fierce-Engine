#include "GL_Renderer_Geometry2D.h"

/**GL_Renderer_Geometry2D::GL_Renderer_Geometry2D(GL_Pipeline* pipeline) {
	m_pipeline = pipeline;
}

void GL_Renderer_Geometry2D::render() {
	m_pipeline->bind();
	for (Entity2D* entity : entities) {
		//Prepare entity
		Mat4 modelMatrix;
		modelMatrix.setToIdentity();
		modelMatrix.transform(entity->getTransform());
		m_pipeline->loadUniform("modelMatrix", &modelMatrix);

		//Load color
		ComponentMaterialColor* color = (ComponentMaterialColor*)(entity->getComponent(ComponentType::MATERIAL_COLOR));
		m_pipeline->loadUniform("color", color->getR(), color->getG(), color->getB());

		//Render entity
		renderEntity(entity);
	}
	m_pipeline->unbind();
}

void GL_Renderer_Geometry2D::renderEntity(Entity2D* entity) {
	ComponentMaterialColors* colors = (ComponentMaterialColors*)(entity->getComponent(ComponentType::MATERIAL_COLORS));
	colors->reset();
	ComponentMesh* mesh = (ComponentMesh*)(entity->getComponent(ComponentType::MESH));
	Color3f* color;
	ComponentGeometry* geo= (ComponentGeometry*)(entity->getComponent(ComponentType::GEOMETRY));
	int count = 0;

	switch (geo->getType()) {
	case RECTANGLE:
	case TRIANGLE:
		color = colors->getNextColor();
		m_pipeline->loadUniform("color", color->getR(), color->getG(), color->getB());
		mesh->render();
		break;
	case CIRCLE:
		if (geo->getAngle() == 360.0f) {
			count = geo->getNumPoints();
		}
		else {
			count = geo->getNumPoints()-1;
		}

		for (int i = 0;i<count;i++) {
			color = colors->getNextColor();
			m_pipeline->loadUniform("color", color->getR(), color->getG(), color->getB());
			mesh->render(i*3,3);
		}
		break;
	case CIRCLE_RING:
		if (geo->getAngle() == 360.0f) {
			count = geo->getNumPoints();
		}
		else {
			count = geo->getNumPoints() - 1;
		}

		for (int i = 0; i < count; i++) {
			color = colors->getNextColor();
			m_pipeline->loadUniform("color", color->getR(), color->getG(), color->getB());
			mesh->render(i * 6, 6);
		}
		break;
	}
}*/