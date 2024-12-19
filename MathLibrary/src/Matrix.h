#pragma once

#include "Vector.h"
#include "Transform.h"

#include "src/FierceStrings.h"

namespace Fierce {

	#define M00 m[0]
	#define M01 m[1]
	#define M02 m[2]
	#define M03 m[3]

	#define M10 m[4]
	#define M11 m[5]
	#define M12 m[6]
	#define M13 m[7]

	#define M20 m[8]
	#define M21 m[9]
	#define M22 m[10]
	#define M23 m[11]

	#define M30 m[12]
	#define M31 m[13]
	#define M32 m[14]
	#define M33 m[15]

	class Logger;

	class Mat4 {

	public:
		Mat4();
		Mat4(float* matrix);
		Mat4(const Mat4& matrix);
		~Mat4();

	public:
		float* get();
		void print(Logger* logger, std::string name);

		void setToIdentity();
		void setToNull();
		void setToTranslation(float x,float y,float z);
		void setToXRotation(float angle);
		void setToYRotation(float angle);
		void setToZRotation(float angle);
		void setToScale(float scaleX,float scaleY,float scaleZ);
		void setToOrthographicProjection(bool forOpenGL, float width, float height,float n,float f);
		void setToPerspectiveProjection(bool forOpenGL, float aspect, float FOV, float n, float f);
		void setToTransform(Transform2D transform);
		void setToTransform(Transform2D* transform);
		void setToTransform(Transform3D transform);
		void setToView(Transform3D transform);

		Mat4* translate(float x,float y,float z);
		Mat4* rotateX(float angle);
		Mat4* rotateY(float angle);
		Mat4* rotateZ(float angle);
		Mat4* scale(float scaleX, float scaleY, float scaleZ);
		Mat4* transform(Transform2D transform);
		Mat4* transform(Transform3D transform);

	public:
		Mat4& operator=(const Mat4 matrix);
		bool operator==(const Mat4& matrix);
		bool operator!=(const Mat4& matrix);

		Mat4& operator+=(const Mat4& matrix);
		Mat4& operator-=(const Mat4& matrix);
		Mat4& operator*=(const Mat4& matrix);
		Mat4& operator*=(float factor);
		Mat4& operator/=(float factor);

	private:
		float* m;
	};

	Mat4 operator+(const Mat4& m1, const Mat4& m2);
	Mat4 operator-(const Mat4& m1, const Mat4& m2);
	Mat4 operator*(const Mat4& m1, const Mat4& m2);

	Mat4 operator*(const Mat4& matrix, float factor);
	Mat4 operator*(float factor, const Mat4& matrix);
	Mat4 operator/(const Mat4& matrix, float factor);

}//end namespace