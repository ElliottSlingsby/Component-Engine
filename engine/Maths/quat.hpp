#pragma once

#include "Vec3.hpp"

struct Quat{
	float w = 1.f;
	float x = 0.f;
	float y = 0.f;
	float z = 0.f;

	Quat();
	Quat(const Quat& other);
	Quat(float w, float x, float y, float z);
	Quat(const Vec3& angles);

	void operator=(const Quat& other);

	Quat operator*(const Quat& other);
	void operator*=(const Quat& other);

	Vec3 operator*(const Vec3& other);
};

Quat conjugate(const Quat& a);

Vec3 eulerAngles(const Quat& a);

Quat inverse(const Quat& a);

float magnitude(const Quat& a);

Quat normalize(const Quat& a);
