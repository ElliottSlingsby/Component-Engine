#pragma once

#include "Quat.hpp"
#include "Vec3.hpp"

struct Mat4{
	float m[4][4];

	Mat4();
	Mat4(const Mat4& other);
	Mat4(float a0, float a1, float a2, float a3, float b0, float b1, float b2, float b3, float c0, float c1, float c2, float c3, float d0, float d1, float d2, float d3);

	const float* gl();
	unsigned int length();

	Mat4 operator*(const Mat4& other);
	void operator*=(const Mat4& other);

	Vec3 operator*(const Vec3& other);
};

Mat4 inverse(const Mat4& a);

Mat4 mat4Cast(const Quat& a);
