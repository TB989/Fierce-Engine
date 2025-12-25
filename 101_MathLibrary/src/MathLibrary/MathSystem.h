#pragma once

#include "src/systems/IMathSystem.h"

namespace Fierce {

    class MathSystem: public IMathSystem {
    public:
        Color4f* createColor(float r, float g, float b, float a) override;
        Transform2D* createTransform2D(float x, float y, float scaleX, float scaleY, float rotation) override;
        Transform3D* createTransform3D(float x, float y, float z, float scaleX, float scaleY, float scaleZ, float rotationX, float rotationY, float rotationZ) override;
        Mat4* createMatrix() override;

        void initSystem(std::string assetDirectory) override;
        void linkSystem(System* system) override;
        void updateSystem() override;
        void cleanUpSystem() override;

        std::string getName() override;
    };
};