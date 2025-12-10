#pragma once

#include "IVector.h"
#include "ITransform.h"

#include <string>

namespace Fierce {

	class Logger;

	class IMat {};

	class IMat4:IMat{
	public:
		virtual ~IMat4()=default;

		virtual float* get()=0;
		virtual void print(Logger* logger, std::string name)=0;

		virtual void setToIdentity()=0;
		virtual void setToNull()=0;
		virtual void setToTranslation(float x,float y,float z)=0;
		virtual void setToXRotation(float angle)=0;
		virtual void setToYRotation(float angle)=0;
		virtual void setToZRotation(float angle)=0;
		virtual void setToScale(float scaleX,float scaleY,float scaleZ)=0;
		virtual void setToOrthographicProjection(bool forOpenGL, float width, float height,float n,float f)=0;
		virtual void setToPerspectiveProjection(bool forOpenGL, float aspect, float FOV, float n, float f)=0;
		virtual void setToTransform(ITransform2D* transform)=0;
		virtual void setToTransform(ITransform3D* transform)=0;
		virtual void setToView(ITransform3D* transform)=0;

		virtual IMat4* translate(float x,float y,float z)=0;
		virtual IMat4* rotateX(float angle)=0;
		virtual IMat4* rotateY(float angle)=0;
		virtual IMat4* rotateZ(float angle)=0;
		virtual IMat4* scale(float scaleX, float scaleY, float scaleZ)=0;
		virtual IMat4* transform(ITransform2D* transform)=0;
		virtual IMat4* transform(ITransform3D* transform)=0;

	public:
		virtual IMat4& operator=(const IMat4& matrix)=0;
		virtual bool operator==(const IMat4& matrix)=0;
		virtual bool operator!=(const IMat4& matrix)=0;

		virtual IMat4& operator+=(const IMat4& matrix)=0;
		virtual IMat4& operator-=(const IMat4& matrix)=0;
		virtual IMat4& operator*=(const IMat4& matrix)=0;
		virtual IMat4& operator*=(float factor)=0;
		virtual IMat4& operator/=(float factor)=0;
	};

}//end namespace