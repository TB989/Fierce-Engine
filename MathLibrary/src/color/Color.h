#pragma once

#include "src/utils/Logging.h"

#define R r
#define G g
#define B b
#define A a

class Color3f{
public:
	Color3f(float r, float g, float b);
	Color3f(float* values);
	Color3f();
	~Color3f();

	float getR() { return R; }
	float getG() { return G; }
	float getB() { return B; }

	void setR(float r) { R = r; }
	void setG(float g) { G = g; }
	void setB(float b) { B = b; }
private:
	float r;
	float g;
	float b;
};

class Color4f {
public:
	Color4f(float r, float g, float b, float a);
	Color4f(float* values);
	Color4f();
	~Color4f();

	float getR() { return R; }
	float getG() { return G; }
	float getB() { return B; }
	float getA() { return A; }

	void setR(float r) { R = r; }
	void setG(float g) { G = g; }
	void setB(float b) { B = b; }
	void setA(float a) { A = a; }
private:
	float r;
	float g;
	float b;
	float a;
};