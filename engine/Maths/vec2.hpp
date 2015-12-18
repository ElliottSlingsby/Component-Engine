#pragma once

struct Vec2{
	float x = 0.f;
	float y = 0.f;

	Vec2();
	Vec2(const Vec2& other);
	Vec2(float x, float y);

	unsigned int length();

	void operator=(const Vec2& other);

	Vec2 operator+(const Vec2& other);
	Vec2 operator-(const Vec2& other);

	Vec2 operator*(const Vec2& other);
	Vec2 operator/(const Vec2& other);

	void operator+=(const Vec2& other);
	void operator-=(const Vec2& other);

	void operator*=(const Vec2& other);
	void operator/=(const Vec2& other);

	Vec2 operator+(float other);
	Vec2 operator-(float other);

	Vec2 operator*(float other);
	Vec2 operator/(float other);

	void operator+=(float other);
	void operator-=(float other);

	void operator*=(float other);
	void operator/=(float other);
};

float dot(const Vec2& a, const Vec2& b);

float magnitude(const Vec2& a);

float distance(const Vec2& a, const Vec2& b);

Vec2 normalize(const Vec2& a);
