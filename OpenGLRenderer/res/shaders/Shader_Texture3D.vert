#version 430 core

layout (location=0) in vec3 position;
layout (location=1) in vec2 textureCoordinate;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec2 vs_textureCoordinate;

void main() {
	vs_textureCoordinate=textureCoordinate;
	gl_Position=projectionMatrix*viewMatrix*modelMatrix*vec4(position,1.0);
}