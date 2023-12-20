#pragma once

#include "src/utils/Logging.h"

#define R c[0]
#define G c[1]
#define B c[2]
#define A c[3]

class Color3f{
public:
	Color3f(float r, float g, float b);
	Color3f(float* values);
	Color3f();
	~Color3f();

	float getR() { return R; }
	float getG() { return G; }
	float getB() { return B; }
	float* get() { return c; }

	void setR(float r) { R = r; }
	void setG(float g) { G = g; }
	void setB(float b) { B = b; }
private:
	float* c=nullptr;
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
	float* get() { return c; }

	void setR(float r) { R = r; }
	void setG(float g) { G = g; }
	void setB(float b) { B = b; }
	void setA(float a) { A = a; }
private:
	float* c=nullptr;
};