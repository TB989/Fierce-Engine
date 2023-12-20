#include "Color.h"

#include "src/utils/Logging.h"

Color3f::Color3f(float r, float g, float b) {
	LOGGER124->warn("Calling 3f constructor.");
	c = new float[3];
	R = r;
	G = g;
	B = b;
}

Color3f::Color3f(float* values) {
	LOGGER124->warn("Calling float* constructor.");
	c = new float[3];
	R = values[0];
	G = values[1];
	B = values[2];
}

Color3f::Color3f() {
	LOGGER124->warn("Calling empty constructor.");
	c = new float[3];
	R = 0.0f;
	G = 0.0f;
	B = 0.0f;
}

Color3f::~Color3f() {
	LOGGER124->warn("Calling delete.");
	//delete[] c;
}

Color4f::Color4f(float r, float g, float b, float a) {
	c = new float[4];
	R = r;
	G = g;
	B = b;
	A = a;
}

Color4f::Color4f(float* values) {
	c = new float[4];
	R = values[0];
	G = values[1];
	B = values[2];
	A = values[3];
}

Color4f::Color4f() {
	c = new float[4];
	R = 0.0f;
	G = 0.0f;
	B = 0.0f;
	A = 0.0f;
}

Color4f::~Color4f() {
	delete[] c;
}