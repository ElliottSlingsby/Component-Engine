#pragma once

struct vec2{
	float x = 0.f;
	float y = 0.f;

	vec2();
	vec2(const vec2& other);
	vec2(float x, float y);

	unsigned int length();
	void* gl();

	void operator=(const vec2& other);

	vec2 operator+(const vec2& other);
	vec2 operator-(const vec2& other);

	vec2 operator*(const vec2& other);
	vec2 operator/(const vec2& other);

	void operator+=(const vec2& other);
	void operator-=(const vec2& other);

	void operator*=(const vec2& other);
	void operator/=(const vec2& other);

	vec2 operator+(float other);
	vec2 operator-(float other);

	vec2 operator*(float other);
	vec2 operator/(float other);

	void operator+=(float other);
	void operator-=(float other);

	void operator*=(float other);
	void operator/=(float other);
};

float dot(const vec2& a, const vec2& b);

float magnitude(const vec2& a);

float distance(const vec2& a, const vec2& b);

vec2 normalize(const vec2& a);