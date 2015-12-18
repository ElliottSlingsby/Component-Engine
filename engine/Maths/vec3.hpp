#pragma once

struct vec3{
	float x = 0.f;
	float y = 0.f;
	float z = 0.f;

	vec3();
	vec3(const vec3& other);
	vec3(float x, float y, float z);

	unsigned int length();
	void* gl();

	void operator=(const vec3& other);

	vec3 operator+(const vec3& other);
	vec3 operator-(const vec3& other);

	vec3 operator*(const vec3& other);
	vec3 operator/(const vec3& other);

	void operator+=(const vec3& other);
	void operator-=(const vec3& other);

	void operator*=(const vec3& other);
	void operator/=(const vec3& other);

	vec3 operator+(float other);
	vec3 operator-(float other);
	   
	vec3 operator*(float other);
	vec3 operator/(float other);

	void operator+=(float other);
	void operator-=(float other);

	void operator*=(float other);
	void operator/=(float other);
};

vec3 cross(const vec3& a, const vec3& b);

float dot(const vec3& a, const vec3& b);

float magnitude(const vec3& a);

float distance(const vec3& a, const vec3& b);

vec3 normalize(const vec3& a);