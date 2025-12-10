#pragma once

#include "IVector.h"

namespace Fierce {

	class ITransform {};

	class ITransform2D : ITransform {
	public:
		virtual ~ITransform2D()=default;

		virtual IVector2f* getPosition()=0;
		virtual IVector2f* getScale()=0;
		virtual float getRotation()=0;
		virtual void setRotation(float rotation)=0;
	};

	class ITransform3D : ITransform {
	public:
		virtual ~ITransform3D() = default;

		virtual IVector3f* getPosition()=0;
		virtual IVector3f* getScale()=0;
		virtual IVector3f* getRotation()=0;
	};

}//end namespace