#include "MathSystem.h"

#include "src/MathLibrary/Color.h"
#include "src/MathLibrary/Vector.h"
#include "src/MathLibrary/Matrix.h"
#include "src/MathLibrary/Transform.h"

namespace Fierce {

	Color4f* Fierce::MathSystem::createColor(float r, float g, float b, float a){
		return new Color4f(r,g,b,a);
	}

	Transform2D* MathSystem::createTransform2D(float x, float y, float scaleX, float scaleY, float rotation){
		return new Transform2D(x,y,scaleX,scaleY,rotation);
	}

	Transform3D* MathSystem::createTransform3D(float x, float y, float z, float scaleX, float scaleY, float scaleZ, float rotationX, float rotationY, float rotationZ){
		return new Transform3D(x, y, z, scaleX, scaleY, scaleZ, rotationX,rotationY,rotationZ);
	}

	Mat4* MathSystem::createMatrix(){
		return new Mat4();
	}

	void MathSystem::initSystem(std::string assetDirectory)	{}
	void MathSystem::linkSystem(System* system)	{}
	void MathSystem::updateSystem()	{}
	void MathSystem::cleanUpSystem(){}

	std::string MathSystem::getName(){
		return "MathSystem";
	}
};