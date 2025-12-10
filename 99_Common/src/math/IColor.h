#pragma once

namespace Fierce {

	class IColor {};

	class IColor3f:IColor{
	public:
		virtual ~IColor3f() = default;

		virtual float getR() = 0;
		virtual float getG() = 0;
		virtual float getB() = 0;

		virtual float* get() = 0;

		virtual void setR(float r) = 0;
		virtual void setG(float g) = 0;
		virtual void setB(float b) = 0;
	};

	class IColor4f:IColor{
	public:
		virtual ~IColor4f() = default;

		virtual float getR() = 0;
		virtual float getG() = 0;
		virtual float getB() = 0;
		virtual float getA() = 0;

		virtual float* get() = 0;

		virtual void setR(float r) = 0;
		virtual void setG(float g) = 0;
		virtual void setB(float b) = 0;
		virtual void setA(float a) = 0;
	};

}//end namespace