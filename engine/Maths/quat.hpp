#pragma once

#include "vec3.hpp"

struct quat{
	float w = 1.f;
	float x = 0.f;
	float y = 0.f;
	float z = 0.f;

	quat();
	quat(float w, float x, float y, float z);
	quat(const vec3& angles);

	void operator=(const quat& other);

	quat operator*(const quat& other);
	void operator*=(const quat& other);

	vec3 operator*(const vec3& other);
};

quat conjugate(const quat& a);

vec3 eulerAngles(const quat& a);

quat inverse(const quat& a);

float magnitude(const quat& a);

quat normalize(const quat& a);