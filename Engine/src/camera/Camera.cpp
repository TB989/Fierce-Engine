#include "Camera.h"

Camera::Camera(){
	m_width = 0.0f;
	m_height = 0.0f;
	m_fov = 0.0f;
	m_nearOrtho = 0.0f;
	m_farOrtho = 0.0f;
	m_nearPersp = 0.0f;
	m_farPersp = 0.0f;
}

Camera::Camera(float width,float height,float fov,float nearOrtho, float farOrtho, float nearPersp,float farPersp){
	m_width = width;
	m_height = height;
	m_fov = fov;
	m_nearOrtho = nearOrtho;
	m_farOrtho = farOrtho;
	m_nearPersp = nearPersp;
	m_farPersp = farPersp;
}