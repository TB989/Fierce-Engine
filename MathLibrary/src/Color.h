#pragma once

namespace Fierce {

	class Color3f{
	public:
		Color3f(float r, float g, float b) {
			m_r = r;
			m_g = g;
			m_b = b;
		}

		float getR() { return m_r; }
		float getG() { return m_g; }
		float getB() { return m_b; }

		void setR(float r) { m_r = r; }
		void setG(float g) { m_g = g; }
		void setB(float b) { m_b = b; }
	private:
		float m_r;
		float m_g;
		float m_b;
	};

	class Color4f {
	public:
		Color4f(float r, float g, float b, float a) {
			m_r = r;
			m_g = g;
			m_b = b;
			m_a = a;
		}

		float getR() { return m_r; }
		float getG() { return m_g; }
		float getB() { return m_b; }
		float getA() { return m_a; }

		void setR(float r) { m_r = r; }
		void setG(float g) { m_g = g; }
		void setB(float b) { m_b = b; }
		void setA(float a) { m_a = a; }
	private:
		float m_r;
		float m_g;
		float m_b;
		float m_a;
	};

}//end namespace