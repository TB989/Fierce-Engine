#pragma once

#define R c[0]
#define G c[1]
#define B c[2]
#define A c[3]

class Color3f{
public:
	Color3f(float r, float g, float b) {
		c=new float[3];
		R = r;
		G = g;
		B = b;
	}

	Color3f(float* values) {
		c = new float[3];
		R = values[0];
		G = values[1];
		B = values[2];
	}

	~Color3f() {
		delete[] c;
	}

	float getR() { return R; }
	float getG() { return G; }
	float getB() { return B; }
	float* get() { return c; }

	void setR(float r) { R = r; }
	void setG(float g) { G = g; }
	void setB(float b) { B = b; }
private:
	float* c;
};

class Color4f {
public:
	Color4f(float r, float g, float b, float a) {
		c = new float[4];
		R = r;
		G = g;
		B = b;
		A = a;
	}

	Color4f(float* values) {
		c = new float[4];
		R = values[0];
		G = values[1];
		B = values[2];
		A = values[3];
	}

	~Color4f() {
		delete[] c;
	}

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
	float* c;
};