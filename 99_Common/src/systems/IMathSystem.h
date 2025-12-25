#pragma once

#include "System.h"

namespace Fierce {

    class Color4f;
    class Transform2D;
    class Transform3D;
    class Mat4;

    class IMathSystem:public System{
    public:
        virtual Color4f* createColor(float r, float g,float b,float a) = 0;
        virtual Transform2D* createTransform2D(float x,float y,float scaleX,float scaleY,float rotation) = 0;
        virtual Transform3D* createTransform3D(float x, float y, float z,float scaleX, float scaleY, float scaleZ, float rotationX,float rotationY,float rotationZ) = 0;
        virtual Mat4* createMatrix()=0;

    };
};