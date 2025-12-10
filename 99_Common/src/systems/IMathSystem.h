#pragma once

#include "../math/IColor.h"
#include "../math/IVector.h"
#include "../math/IMatrix.h"
#include "../math/ITransform.h"

namespace Fierce {

    class IMathSystem{
    public:
        virtual IColor4f* createColor(float r, float g,float b,float a) = 0;
        virtual ITransform2D* createTransform2D(float x,float y,float scaleX,float scaleY,float rotation) = 0;
        virtual ITransform3D* createTransform3D(float x, float y, float z,float scaleX, float scaleY, float scaleZ, float rotationX,float rotationY,float rotationZ) = 0;
        virtual IMat4* createMatrix()=0;

    };
};