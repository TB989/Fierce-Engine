#include "Color.h"

#include "src/utils/Logging.h"

Color3f::Color3f(float r, float g, float b) {
	R = r;
	G = g;
	B = b;
}

Color3f::Color3f(float* values) {
	R = values[0];
	G = values[1];
	B = values[2];
}

Color3f::Color3f() {
	R = 0.0f;
	G = 0.0f;
	B = 0.0f;
}

Color3f::~Color3f() {
	
}

Color4f::Color4f(float r, float g, float b, float a) {
	R = r;
	G = g;
	B = b;
	A = a;
}

Color4f::Color4f(float* values) {
	R = values[0];
	G = values[1];
	B = values[2];
	A = values[3];
}

Color4f::Color4f() {
	R = 0.0f;
	G = 0.0f;
	B = 0.0f;
	A = 0.0f;
}

Color4f::~Color4f() {
	
}