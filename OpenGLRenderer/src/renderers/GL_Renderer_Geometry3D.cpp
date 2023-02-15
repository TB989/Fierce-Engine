#include "GL_Renderer_Geometry3D.h"

GL_Renderer_Geometry3D::GL_Renderer_Geometry3D(GL_Pipeline* pipeline) {
	m_pipeline = pipeline;
}

void GL_Renderer_Geometry3D::render() {
	m_pipeline->bind();
	for (Entity3D* entity : entities) {
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

void GL_Renderer_Geometry3D::renderEntity(Entity3D* entity) {
	ComponentMaterialColors* colors = (ComponentMaterialColors*)(entity->getComponent(ComponentType::MATERIAL_COLORS));
	colors->reset();
	ComponentMesh* mesh = (ComponentMesh*)(entity->getComponent(ComponentType::MESH));
	Color3f* color;
	ComponentGeometry* geo = (ComponentGeometry*)(entity->getComponent(ComponentType::GEOMETRY));
	int count = 0;

	switch (geo->getType()) {
	case PLANE:
		color = colors->getNextColor();
		m_pipeline->loadUniform("color", color->getR(), color->getG(), color->getB());
		mesh->render();
		break;
	case CUBE:
		for (int i = 0;i<6;i++) {
			color = colors->getNextColor();
			m_pipeline->loadUniform("color", color->getR(), color->getG(), color->getB());
			mesh->render(i*6, 6);
		}
		break;
	case CYLINDER:
		if (geo->getAngle() == 360.0f) {
			count = geo->getNumPoints();
		}
		else {
			count = geo->getNumPoints() - 1;
		}

		color = colors->getNextColor();
		m_pipeline->loadUniform("color", color->getR(), color->getG(), color->getB());
		mesh->render(0, 3*count);
		color = colors->getNextColor();
		m_pipeline->loadUniform("color", color->getR(), color->getG(), color->getB());
		mesh->render(3 * count, 3 * count);
		color = colors->getNextColor();
		m_pipeline->loadUniform("color", color->getR(), color->getG(), color->getB());
		mesh->render(6 * count, 6 * count);

		if (geo->getAngle() != 360.0f) {
			color = colors->getNextColor();
			m_pipeline->loadUniform("color", color->getR(), color->getG(), color->getB());
			mesh->render(12*count, 6);
			color = colors->getNextColor();
			m_pipeline->loadUniform("color", color->getR(), color->getG(), color->getB());
			mesh->render(12 * count+6, 6);
		}

		break;
	case HOLLOW_CYLINDER:
		if (geo->getAngle() == 360.0f) {
			count = geo->getNumPoints();
		}
		else {
			count = geo->getNumPoints() - 1;
		}

		color = colors->getNextColor();
		m_pipeline->loadUniform("color", color->getR(), color->getG(), color->getB());
		mesh->render(0, 6 * count);
		color = colors->getNextColor();
		m_pipeline->loadUniform("color", color->getR(), color->getG(), color->getB());
		mesh->render(6 * count, 6 * count);
		color = colors->getNextColor();
		m_pipeline->loadUniform("color", color->getR(), color->getG(), color->getB());
		mesh->render(12 * count, 6 * count);
		color = colors->getNextColor();
		m_pipeline->loadUniform("color", color->getR(), color->getG(), color->getB());
		mesh->render(18 * count, 6 * count);

		if (geo->getAngle() != 360.0f) {
			color = colors->getNextColor();
			m_pipeline->loadUniform("color", color->getR(), color->getG(), color->getB());
			mesh->render(24 * count, 6);
			color = colors->getNextColor();
			m_pipeline->loadUniform("color", color->getR(), color->getG(), color->getB());
			mesh->render(24 * count + 6, 6);
		}

		break;
	case CONE:
		if (geo->getAngle() == 360.0f) {
			count = geo->getNumPoints();
		}
		else {
			count = geo->getNumPoints() - 1;
		}

		color = colors->getNextColor();
		m_pipeline->loadUniform("color", color->getR(), color->getG(), color->getB());
		mesh->render(0, 3 * count);
		color = colors->getNextColor();
		m_pipeline->loadUniform("color", color->getR(), color->getG(), color->getB());
		mesh->render(3 * count, 3 * count);

		if (geo->getAngle() != 360.0f) {
			color = colors->getNextColor();
			m_pipeline->loadUniform("color", color->getR(), color->getG(), color->getB());
			mesh->render(6 * count, 3);
			color = colors->getNextColor();
			m_pipeline->loadUniform("color", color->getR(), color->getG(), color->getB());
			mesh->render(6 * count + 3, 3);
		}

		break;
	case SPHERE:
		if (geo->getAngle() == 360.0f) {
			count = geo->getNumPoints();
		}
		else {
			count = geo->getNumPoints() - 1;
		}

		int counter = 0;

		//Circle
		color = colors->getNextColor();
		m_pipeline->loadUniform("color", color->getR(), color->getG(), color->getB());
		mesh->render(counter, 3 * count);
		counter += 3 * count;

		//Circle rings
		for (int i = 0;i<geo->getNumRings()-1;i++) {
			color = colors->getNextColor();
			m_pipeline->loadUniform("color", color->getR(), color->getG(), color->getB());
			mesh->render(counter, 6 * count);
			counter += 6 * count;
		}

		//Circle
		color = colors->getNextColor();
		m_pipeline->loadUniform("color", color->getR(), color->getG(), color->getB());
		mesh->render(counter, 3 * count);

		break;
	}
}