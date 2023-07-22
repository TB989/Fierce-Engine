#version 430 core

layout (location=0) in vec2 position;
layout (location=1) in vec2 textureCoordinate;

uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;

out vec2 vs_textureCoordinate;

void main() {
	vs_textureCoordinate=textureCoordinate;
	gl_Position=projectionMatrix*modelMatrix*vec4(position,0.0,1.0);
}