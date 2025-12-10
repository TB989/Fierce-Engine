#pragma once

#include <string>

namespace Fierce {
	class Logger;

	class IVector {};

	class IVector2f:IVector{

	public:
		virtual ~IVector2f()=default;

		virtual float length()=0;
		virtual float lengthSquared()=0;
		virtual float distance(const IVector2f* vector)=0;
		virtual float distanceSquared(const IVector2f* vector)=0;

		virtual void normalize()=0;

		virtual void print(Logger* logger, std::string name)=0;

	public:
		virtual float* get()=0;
		virtual float getX()=0;
		virtual float getY()=0;
		virtual void setX(float x)=0;
		virtual void setY(float y)=0;
		virtual void setTo(const IVector2f* vector)=0;
		virtual void setTo(float x, float y)=0;

	public:
		virtual IVector2f& operator=(const IVector2f& vector)=0;
		virtual bool operator==(const IVector2f& vector)=0;
		virtual bool operator!=(const IVector2f& vector)=0;

		virtual IVector2f& operator+=(const IVector2f& vector)=0;
		virtual IVector2f& operator-=(const IVector2f& vector)=0;
		virtual IVector2f& operator*=(const IVector2f& vector)=0;
		virtual IVector2f& operator/=(const IVector2f& vector)=0;
		virtual IVector2f& operator*=(float factor)=0;
		virtual IVector2f& operator/=(float factor)=0;
	};

	class IVector3f:IVector{
	public:
		virtual virtual ~IVector3f()=default;

		virtual float length()=0;
		virtual float lengthSquared()=0;
		virtual float distance(const IVector3f* vector)=0;
		virtual float distanceSquared(const IVector3f* vector)=0;

		virtual void normalize()=0;

		virtual void print(Logger* logger, std::string name)=0;

	public:
		virtual float* get()=0;
		virtual float getX()=0;
		virtual float getY()=0;
		virtual float getZ()=0;
		virtual void setX(float x)=0;
		virtual void setY(float y)=0;
		virtual void setZ(float z)=0;
		virtual void setTo(const IVector3f* vector)=0;
		virtual void setTo(float x, float y, float z)=0;

	public:
		virtual IVector3f& operator=(const IVector3f& vector)=0;
		virtual bool operator==(const IVector3f& vector)=0;
		virtual bool operator!=(const IVector3f& vector)=0;

		virtual IVector3f& operator+=(const IVector3f& vector)=0;
		virtual IVector3f& operator-=(const IVector3f& vector)=0;
		virtual IVector3f& operator*=(const IVector3f& vector)=0;
		virtual IVector3f& operator/=(const IVector3f& vector)=0;
		virtual IVector3f& operator*=(float factor)=0;
		virtual IVector3f& operator/=(float factor)=0;
	};

	class IVector4f:IVector{
	public:
		virtual ~IVector4f()=default;

		virtual float length()=0;
		virtual float lengthSquared()=0;
		virtual float distance(const IVector4f* vector)=0;
		virtual float distanceSquared(const IVector4f* vector)=0;

		virtual void normalize()=0;

		virtual void print(Logger* logger, std::string name)=0;

	public:
		virtual float* get()=0;
		virtual float getX()=0;
		virtual float getY()=0;
		virtual float getZ()=0;
		virtual float getW()=0;
		virtual void setX(float x)=0;
		virtual void setY(float y)=0;
		virtual void setZ(float z)=0;
		virtual void setW(float w)=0;
		virtual void setTo(const IVector4f* vector)=0;
		virtual void setTo(float x, float y, float z, float w)=0;

	public:
		virtual IVector4f& operator=(const IVector4f& vector)=0;
		virtual bool operator==(const IVector4f& vector)=0;
		virtual bool operator!=(const IVector4f& vector)=0;

		virtual IVector4f& operator+=(const IVector4f& vector)=0;
		virtual IVector4f& operator-=(const IVector4f& vector)=0;
		virtual IVector4f& operator*=(const IVector4f& vector)=0;
		virtual IVector4f& operator/=(const IVector4f& vector)=0;
		virtual IVector4f& operator*=(float factor)=0;
		virtual IVector4f& operator/=(float factor)=0;
	};

}//end namespace