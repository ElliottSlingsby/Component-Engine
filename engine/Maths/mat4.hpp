#pragma once

#include "quat.hpp"
#include "vec3.hpp"

class mat4{
	float matrix[4][4] = {
		{ 1.f, 0.f, 0.f, 0.f },
		{ 0.f, 1.f, 0.f, 0.f },
		{ 0.f, 0.f, 1.f, 0.f },
		{ 0.f, 0.f, 0.f, 1.f }
	};

public:
	mat4(float a0, float a1, float a2, float a3,
		float b0, float b1, float b2, float b3,
		float c0, float c1, float c2, float c3,
		float d0, float d1, float d2, float d3
	);

	void* gl();
	unsigned int length();

	float operator[](unsigned int);

	mat4 operator*(const quat& other);
	void operator*=(const quat& other);

	vec3 operator*(const vec3& other);
};

mat4 inverse(const mat4& a);

mat4 mat4Cast(const quat& a);
