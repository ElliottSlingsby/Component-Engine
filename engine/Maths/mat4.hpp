#pragma once

#include "quat.hpp"
#include "vec3.hpp"

struct mat4{
	float m[4][4];

	mat4();
	mat4(const mat4& other);
	mat4(float a0, float a1, float a2, float a3, float b0, float b1, float b2, float b3, float c0, float c1, float c2, float c3, float d0, float d1, float d2, float d3);

	void* gl();
	unsigned int length();

	mat4 operator*(const mat4& other);
	void operator*=(const mat4& other);

	vec3 operator*(const vec3& other);
};

mat4 inverse(const mat4& a);

mat4 mat4Cast(const quat& a);
