#pragma once

class Camera {
public:
	Camera();
	Camera(float width, float height, float fov, float nearOrtho, float farOrtho, float nearPersp, float farPersp);

	float getWidth() { return m_width; }
	float getHeight() { return m_height; }
	float getAspect() { return m_width/m_height; }
	float getFOV() { return m_fov; }

	float getNearOrtho() { return m_nearOrtho; }
	float getFarOrtho() { return m_farOrtho; }
	float getNearPerspective() { return m_nearPersp; }
	float getFarPerspective() { return m_farPersp; }

private:
	float m_width,m_height;
	float m_fov;
	float m_nearOrtho, m_farOrtho;
	float m_nearPersp, m_farPersp;
};