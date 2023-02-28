#include "GL_Renderer_Color3D.h"

/**GL_Renderer_Color3D::GL_Renderer_Color3D(GL_Pipeline* pipeline) {
	m_pipeline = pipeline;
}

void GL_Renderer_Color3D::render() {
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
		ComponentMesh* mesh = (ComponentMesh*)(entity->getComponent(ComponentType::MESH));
		mesh->render();
	}
	m_pipeline->unbind();
}*/