#include "Matrix.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include "src/Logger.h"

namespace Fierce {

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Mat4::Mat4() {
		m = new float [16];

		M00 = 1;
		M10 = 0;
		M20 = 0;
		M30 = 0;

		M01 = 0;
		M11 = 1;
		M21 = 0;
		M31 = 0;

		M02 = 0;
		M12 = 0;
		M22 = 1;
		M32 = 0;

		M03 = 0;
		M13 = 0;
		M23 = 0;
		M33 = 1;
	}

	Mat4::Mat4(float* matrix){
		m = new float[16];
		for (int i = 0; i < 16; i++) {
			m[i] = matrix[i];
		}
	}

	Mat4::Mat4(const Mat4& matrix){
		m = new float[16];
		for (int i = 0; i < 16; i++) {
			m[i] = matrix.m[i];
		}
	}

	Mat4::~Mat4(){
		delete[] m;
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	float* Mat4::get(){
		return m;
	}

	void Mat4::print(Logger* logger, std::string name){
		logger->info("[Matrix %s]:", name.c_str());
		logger->info("%1.3f %1.3f %1.3f %1.3f", M00, M10, M20, M30);
		logger->info("%1.3f %1.3f %1.3f %1.3f", M01, M11, M21, M31);
		logger->info("%1.3f %1.3f %1.3f %1.3f", M02, M12, M22, M32);
		logger->info("%1.3f %1.3f %1.3f %1.3f", M03, M13, M23, M33);
	}

	void Mat4::setToIdentity(){
		M00 = 1;
		M10 = 0;
		M20 = 0;
		M30 = 0;

		M01 = 0;
		M11 = 1;
		M21 = 0;
		M31 = 0;

		M02 = 0;
		M12 = 0;
		M22 = 1;
		M32 = 0;

		M03 = 0;
		M13 = 0;
		M23 = 0;
		M33 = 1;
	}

	void Mat4::setToNull(){
		M00 = 0;
		M10 = 0;
		M20 = 0;
		M30 = 0;

		M01 = 0;
		M11 = 0;
		M21 = 0;
		M31 = 0;

		M02 = 0;
		M12 = 0;
		M22 = 0;
		M32 = 0;

		M03 = 0;
		M13 = 0;
		M23 = 0;
		M33 = 0;
	}

	void Mat4::setToTranslation(float x, float y, float z){
		M00 = 1;
		M10 = 0;
		M20 = 0;
		M30 = x;

		M01 = 0;
		M11 = 1;
		M21 = 0;
		M31 = y;

		M02 = 0;
		M12 = 0;
		M22 = 1;
		M32 = z;

		M03 = 0;
		M13 = 0;
		M23 = 0;
		M33 = 1;
	}

	void Mat4::setToXRotation(float angle){
		float s = sin(M_PI / 180.0f * angle);
		float c = cos(M_PI / 180.0f * angle);

		M00 = 1;
		M10 = 0;
		M20 = 0;
		M30 = 0;

		M01 = 0;
		M11 = c;
		M21 = -s;
		M31 = 0;

		M02 = 0;
		M12 = s;
		M22 = c;
		M32 = 0;

		M03 = 0;
		M13 = 0;
		M23 = 0;
		M33 = 1;
	}

	void Mat4::setToYRotation(float angle){
		float s = sin(M_PI / 180.0f * angle);
		float c = cos(M_PI / 180.0f * angle);

		M00 = c;
		M10 = 0;
		M20 = s;
		M30 = 0;

		M01 = 0;
		M11 = 1;
		M21 = 0;
		M31 = 0;

		M02 = -s;
		M12 = 0;
		M22 = c;
		M32 = 0;

		M03 = 0;
		M13 = 0;
		M23 = 0;
		M33 = 1;
	}

	void Mat4::setToZRotation(float angle){
		float s = sin(M_PI / 180.0f * angle);
		float c = cos(M_PI / 180.0f * angle);

		M00 = c;
		M10 = -s;
		M20 = 0;
		M30 = 0;

		M01 = s;
		M11 = c;
		M21 = 0;
		M31 = 0;

		M02 = 0;
		M12 = 0;
		M22 = 1;
		M32 = 0;

		M03 = 0;
		M13 = 0;
		M23 = 0;
		M33 = 1;
	}

	void Mat4::setToScale(float scaleX, float scaleY, float scaleZ){
		M00 = scaleX;
		M10 = 0;
		M20 = 0;
		M30 = 0;

		M01 = 0;
		M11 = scaleY;
		M21 = 0;
		M31 = 0;

		M02 = 0;
		M12 = 0;
		M22 = scaleZ;
		M32 = 0;

		M03 = 0;
		M13 = 0;
		M23 = 0;
		M33 = 1;
	}

	/*
	* OpenGL
	* 2/width 0        0             0
	* 0       2/height 0             0
	* 0       0        -2/(far-near) -(far+near)/(far-near)
	* 0       0        0             1
	*
	* Vulkan
	* 2/width 0         0             0
	* 0       -2/height 0             0
	* 0       0         1/(far-near)  near/(far-near)
	* 0       0         0             1
	*/
	void Mat4::setToOrthographicProjection(bool forOpenGL, float width, float height, float n, float f){
		if (forOpenGL) {
			M00 = 2.0f / width;
			M10 = 0;
			M20 = 0;
			M30 = 0;

			M01 = 0;
			M11 = 2.0f / height;
			M21 = 0;
			M31 = 0;

			M02 = 0;
			M12 = 0;
			M22 = 2.0f / (n - f);
			M32 = (n + f) / (n - f);

			M03 = 0;
			M13 = 0;
			M23 = 0;
			M33 = 1;
		}
		else {
			M00 = 2.0f / width;
			M10 = 0;
			M20 = 0;
			M30 = -1.0f;

			M01 = 0;
			M11 = 2.0f / height;
			M21 = 0;
			M31 = -1.0f;

			M02 = 0;
			M12 = 0;
			M22 = 1.0f / (f - n);
			M32 = n / (f - n);

			M03 = 0;
			M13 = 0;
			M23 = 0;
			M33 = 1;
		}
	}

	/*
	* OpenGL
	* 1/(aspect*tan(FOV/2)) 0               0                      0
	* 0                     1/(tan(FOV/2))  0                      0
	* 0                     0               -(far+near)/(far-near) -(2*far*near)/(far-near)
	* 0                     0               -1                     0
	* 
	* Vulkan
	* 1/(aspect*tan(FOV/2)) 0                0              0
	* 0                     -1/(tan(FOV/2))  0              0
	* 0                     0                far/(far-near) -(far*near)/(far-near)
	* 0                     0                1              0
	*/
	void Mat4::setToPerspectiveProjection(bool forOpenGL,float aspect, float FOV, float n, float f){
		float t = tanf(M_PI *FOV / 360.0f);

		if (forOpenGL) {
			M00 = 1.0f / (t * aspect);
			M10 = 0;
			M20 = 0;
			M30 = 0;

			M01 = 0;
			M11 = 1.0f / t;
			M21 = 0;
			M31 = 0;

			M02 = 0;
			M12 = 0;
			M22 = (n + f) / (n - f);
			M32 = 2 * n * f / (n - f);

			M03 = 0;
			M13 = 0;
			M23 = -1;
			M33 = 0;
		}
		else {
			M00 = 1.0f / (t * aspect);
			M10 = 0;
			M20 = 0;
			M30 = 0;

			M01 = 0;
			M11 = -1.0f / t;
			M21 = 0;
			M31 = 0;

			M02 = 0;
			M12 = 0;
			M22 = f / (f - n);
			M32 = n * f / (n - f);

			M03 = 0;
			M13 = 0;
			M23 = 1;
			M33 = 0;
		}
	}

	void Mat4::setToTransform(Transform2D transform){
		this->setToScale(transform.getScale().getX(), transform.getScale().getY(),1);
		this->rotateZ(transform.getRotation());
		this->translate(transform.getPosition().getX(),transform.getPosition().getY(),0);
	}

	void Mat4::setToTransform(Transform2D* transform){
		this->setToScale(transform->getScale().getX(), transform->getScale().getY(), 1);
		this->rotateZ(transform->getRotation());
		this->translate(transform->getPosition().getX(), transform->getPosition().getY(), 0);
	}

	void Mat4::setToTransform(Transform3D transform){
		this->setToScale(transform.getScale().getX(), transform.getScale().getY(), transform.getScale().getZ());
		this->rotateX(transform.getRotation().getX());
		this->rotateY(transform.getRotation().getY());
		this->rotateZ(transform.getRotation().getZ());
		this->translate(transform.getPosition().getX(), transform.getPosition().getY(), transform.getPosition().getZ());
	}

	void Mat4::setToTransform(Transform3D* transform){
		this->setToScale(transform->getScale().getX(), transform->getScale().getY(), transform->getScale().getZ());
		this->rotateX(transform->getRotation().getX());
		this->rotateY(transform->getRotation().getY());
		this->rotateZ(transform->getRotation().getZ());
		this->translate(transform->getPosition().getX(), transform->getPosition().getY(), transform->getPosition().getZ());
	}

	void Mat4::setToView(Transform3D transform){
		this->setToTranslation(-transform.getPosition().getX(), -transform.getPosition().getY(), -transform.getPosition().getZ());
		this->rotateZ(transform.getRotation().getZ());
		this->rotateY(transform.getRotation().getY());
		this->rotateX(transform.getRotation().getX());
		this->scale(transform.getScale().getX(), transform.getScale().getY(), transform.getScale().getZ());
	}

	void Mat4::setToView(Transform3D* transform){
		this->setToTranslation(-transform->getPosition().getX(), -transform->getPosition().getY(), -transform->getPosition().getZ());
		this->rotateZ(transform->getRotation().getZ());
		this->rotateY(transform->getRotation().getY());
		this->rotateX(transform->getRotation().getX());
		this->scale(transform->getScale().getX(), transform->getScale().getY(), transform->getScale().getZ());
	}

	Mat4* Mat4::translate(float x, float y, float z){
		float temp1 = M03 * x;
		float temp2 = M13 * x;
		float temp3 = M23 * x;
		float temp4 = M33 * x;

		float temp5 = M03 * y;
		float temp6 = M13 * y;
		float temp7 = M23 * y;
		float temp8 = M33 * y;

		float temp9  = M03 * z;
		float temp10 = M13 * z;
		float temp11 = M23 * z;
		float temp12 = M33 * z;

		M00 = M00 + temp1;
		M10 = M10 + temp2;
		M20 = M20 + temp3;
		M30 = M30 + temp4;

		M01 = M01 + temp5;
		M11 = M11 + temp6;
		M21 = M21 + temp7;
		M31 = M31 + temp8;

		M02 = M02 + temp9;
		M12 = M12 + temp10;
		M22 = M22 + temp11;
		M32 = M32 + temp12;
		return this;
	}

	Mat4* Mat4::rotateX(float angle){
		float s = sin(M_PI / 180.0f * angle);
		float c = cos(M_PI / 180.0f * angle);

		float temp1 = M01 * c - M02 * s;
		float temp2 = M11 * c - M12 * s;
		float temp3 = M21 * c - M22 * s;
		float temp4 = M31 * c - M32 * s;

		float temp5 = M01 * s + M02 * c;
		float temp6 = M11 * s + M12 * c;
		float temp7 = M21 * s + M22 * c;
		float temp8 = M31 * s + M32 * c;

		M01 = temp1;
		M11 = temp2;
		M21 = temp3;
		M31 = temp4;

		M02 = temp5;
		M12 = temp6;
		M22 = temp7;
		M32 = temp8;

		return this;
	}

	Mat4* Mat4::rotateY(float angle){
		float s = sin(M_PI / 180.0f * angle);
		float c = cos(M_PI / 180.0f * angle);

		float temp1 = M00 * c + M02 * s;
		float temp2 = M10 * c + M12 * s;
		float temp3 = M20 * c + M22 * s;
		float temp4 = M30 * c + M32 * s;

		float temp5 = - M00 * s + M02 * c;
		float temp6 = - M10 * s + M12 * c;
		float temp7 = - M20 * s + M22 * c;
		float temp8 = - M30 * s + M32 * c;

		M00 = temp1;
		M10 = temp2;
		M20 = temp3;
		M30 = temp4;

		M02 = temp5;
		M12 = temp6;
		M22 = temp7;
		M32 = temp8;

		return this;
	}

	Mat4* Mat4::rotateZ(float angle){
		float s = sin(M_PI / 180.0f * angle);
		float c = cos(M_PI / 180.0f * angle);

		float temp1 = M00 * c - M01 * s;
		float temp2 = M10 * c - M11 * s;
		float temp3 = M20 * c - M21 * s;
		float temp4 = M30 * c - M31 * s;

		float temp5 = M00 * s + M01 * c;
		float temp6 = M10 * s + M11 * c;
		float temp7 = M20 * s + M21 * c;
		float temp8 = M30 * s + M31 * c;

		M00 = temp1;
		M10 = temp2;
		M20 = temp3;
		M30 = temp4;

		M01 = temp5;
		M11 = temp6;
		M21 = temp7;
		M31 = temp8;

		return this;
	}

	Mat4* Mat4::scale(float scaleX, float scaleY, float scaleZ){
		M00 = M00*scaleX;
		M10 = M10*scaleX;
		M20 = M20*scaleX;
		M30 = M30*scaleX;

		M01 = M01*scaleY;
		M11 = M11*scaleY;
		M21 = M21*scaleY;
		M31 = M31*scaleY;

		M02 = M02*scaleZ;
		M12 = M12*scaleZ;
		M22 = M22*scaleZ;
		M32 = M32*scaleZ;
		return this;
	}

	Mat4* Mat4::transform(Transform2D transform){
		this->scale(transform.getScale().getX(), transform.getScale().getY(), 1);
		this->rotateZ(transform.getRotation());
		this->translate(transform.getPosition().getX(), transform.getPosition().getY(), 0);
		return this;
	}

	Mat4* Mat4::transform(Transform3D transform){
		this->scale(transform.getScale().getX(), transform.getScale().getY(), transform.getScale().getZ());
		this->rotateX(transform.getRotation().getX());
		this->rotateY(transform.getRotation().getY());
		this->rotateZ(transform.getRotation().getZ());
		this->translate(transform.getPosition().getX(), transform.getPosition().getY(), transform.getPosition().getZ());
		return this;
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Mat4& Mat4::operator=(const Mat4 matrix){
		if (this == &matrix) {
			return *this;
		}

		for (int i = 0; i < 16; i++) {
			m[i] = matrix.m[i];
		}

		return *this;
	}

	bool Mat4::operator==(const Mat4& matrix){
		return 
			M00 == matrix.M00 &&
			M10 == matrix.M10 &&
			M20 == matrix.M20 &&
			M30 == matrix.M30 &&

			M01 == matrix.M01 &&
			M11 == matrix.M11 &&
			M21 == matrix.M21 &&
			M31 == matrix.M31 &&

			M02 == matrix.M02 &&
			M12 == matrix.M12 &&
			M22 == matrix.M22 &&
			M32 == matrix.M32 &&

			M03 == matrix.M03 &&
			M13 == matrix.M13 &&
			M23 == matrix.M23 &&
			M33 == matrix.M33;
	}

	bool Mat4::operator!=(const Mat4& matrix){
		return !(*this==matrix);
	}

	Mat4& Mat4::operator+=(const Mat4& matrix){
		for (int i = 0; i < 16; i++) {
			m[i] += matrix.m[i];
		}
		return *this;
	}

	Mat4& Mat4::operator-=(const Mat4& matrix) {
		for (int i = 0; i < 16; i++) {
			m[i] -= matrix.m[i];
		}
		return *this;
	}

	Mat4& Mat4::operator*=(const Mat4& matrix){
		float temp[16];

		temp[0] = M00 * matrix.M00 + M10 * matrix.M01 + M20 * matrix.M02 + M30 * matrix.M03;
		temp[1] = M00 * matrix.M10 + M10 * matrix.M11 + M20 * matrix.M12 + M30 * matrix.M13;
		temp[2] = M00 * matrix.M20 + M10 * matrix.M21 + M20 * matrix.M22 + M30 * matrix.M23;
		temp[3] = M00 * matrix.M30 + M10 * matrix.M31 + M20 * matrix.M32 + M30 * matrix.M33;

		temp[4] = M01 * matrix.M00 + M11 * matrix.M01 + M21 * matrix.M02 + M31 * matrix.M03;
		temp[5] = M01 * matrix.M10 + M11 * matrix.M11 + M21 * matrix.M12 + M31 * matrix.M13;
		temp[6] = M01 * matrix.M20 + M11 * matrix.M21 + M21 * matrix.M22 + M31 * matrix.M23;
		temp[7] = M01 * matrix.M30 + M11 * matrix.M31 + M21 * matrix.M32 + M31 * matrix.M33;

		temp[8] = M02 * matrix.M00 + M12 * matrix.M01 + M22 * matrix.M02 + M32 * matrix.M03;
		temp[9] = M02 * matrix.M10 + M12 * matrix.M11 + M22 * matrix.M12 + M32 * matrix.M13;
		temp[10] =M02 * matrix.M20 + M12 * matrix.M21 + M22 * matrix.M22 + M32 * matrix.M23;
		temp[11] =M02 * matrix.M30 + M12 * matrix.M31 + M22 * matrix.M32 + M32 * matrix.M33;

		temp[12] =M03 * matrix.M00 + M13 * matrix.M01 + M23 * matrix.M02 + M33 * matrix.M03;
		temp[13] =M03 * matrix.M10 + M13 * matrix.M11 + M23 * matrix.M12 + M33 * matrix.M13;
		temp[14] =M03 * matrix.M20 + M13 * matrix.M21 + M23 * matrix.M22 + M33 * matrix.M23;
		temp[15] =M03 * matrix.M30 + M13 * matrix.M31 + M23 * matrix.M32 + M33 * matrix.M33;

		for (int i = 0; i < 16; i++) {
			m[i] *= temp[i];
		}

		return *this;
	}

	Mat4& Mat4::operator*=(float factor){
		for (int i = 0; i < 16; i++) {
			m[i] *= factor;
		}
		return *this;
	}

	Mat4& Mat4::operator/=(float factor){
		for (int i = 0; i < 16; i++) {
			m[i] /= factor;
		}
		return *this;
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Mat4 operator+(const Mat4& m1, const Mat4& m2){
		Mat4 temp(m1);
		return (temp += m2);
	}

	Mat4 operator-(const Mat4& m1, const Mat4& m2){
		Mat4 temp(m1);
		return (temp -= m2);
	}

	Mat4 operator*(const Mat4& m1, const Mat4& m2){
		Mat4 temp(m1);
		return (temp *= m2);
	}

	Mat4 operator*(const Mat4& matrix, float factor){
		Mat4 temp(matrix);
		return (temp *= factor);
	}

	Mat4 operator*(float factor, const Mat4& matrix){
		return (matrix * factor);
	}

	Mat4 operator/(const Mat4& matrix, float factor){
		Mat4 temp(matrix);
		return (temp /= factor);
	}

}//end namespace