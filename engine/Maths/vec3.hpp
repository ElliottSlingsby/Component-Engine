#pragma once

struct Vec3{
	float x = 0.f;
	float y = 0.f;
	float z = 0.f;

	Vec3();
	Vec3(const Vec3& other);
	Vec3(float x, float y, float z);

	unsigned int length();

	void operator=(const Vec3& other);

	Vec3 operator+(const Vec3& other);
	Vec3 operator-(const Vec3& other);

	Vec3 operator*(const Vec3& other);
	Vec3 operator/(const Vec3& other);

	void operator+=(const Vec3& other);
	void operator-=(const Vec3& other);

	void operator*=(const Vec3& other);
	void operator/=(const Vec3& other);

	Vec3 operator+(float other);
	Vec3 operator-(float other);
	   
	Vec3 operator*(float other);
	Vec3 operator/(float other);

	void operator+=(float other);
	void operator-=(float other);

	void operator*=(float other);
	void operator/=(float other);
};

Vec3 cross(const Vec3& a, const Vec3& b);

float dot(const Vec3& a, const Vec3& b);

float magnitude(const Vec3& a);

float distance(const Vec3& a, const Vec3& b);

Vec3 normalize(const Vec3& a);
