#include "Vec3.hpp"

#define _USE_MATH_DEFINES
#include <cmath>

// Methods
Vec3::Vec3(){}

Vec3::Vec3(const Vec3& other){
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
}

Vec3::Vec3(float x, float y, float z){
	this->x = x;
	this->y = y;
	this->z = z;
}

unsigned int length(){
	return 3;
}

void Vec3::operator=(const Vec3& other){
	x = other.x;
	y = other.y;
	z = other.z;
}

Vec3 Vec3::operator+(const Vec3& other){
	return Vec3(x + other.x, y + other.y, z + other.z);
}

Vec3 Vec3::operator-(const Vec3& other){
	return Vec3(x - other.x, y - other.y, z - other.z);
}

Vec3 Vec3::operator*(const Vec3& other){
	return Vec3(x * other.x, y * other.y, z * other.z);
}

Vec3 Vec3::operator/(const Vec3& other){
	return Vec3(x / other.x, y / other.y, z / other.z);
}

void Vec3::operator+=(const Vec3& other){
	x += other.x;
	y += other.y;
	z += other.z;
}

void Vec3::operator-=(const Vec3& other){
	x -= other.x;
	y -= other.y;
	z -= other.z;
}

void Vec3::operator*=(const Vec3& other){
	x *= other.x;
	y *= other.y;
	z *= other.z;
}
void Vec3::operator/=(const Vec3& other){
	x /= other.x;
	y /= other.y;
	z /= other.z;
}

Vec3 Vec3::operator+(float other){
	return Vec3(x + other, y + other, z + other);
}

Vec3 Vec3::operator-(float other){
	return Vec3(x - other, y - other, z - other);
}

Vec3 Vec3::operator*(float other){
	return Vec3(x * other, y * other, z * other);
}

Vec3 Vec3::operator/(float other){
	return Vec3(x / other, y / other, z / other);
}

void Vec3::operator+=(float other){
	x += other;
	y += other;
	z += other;
}

void Vec3::operator-=(float other){
	x -= other;
	y -= other;
	z -= other;
}


void Vec3::operator*=(float other){
	x *= other;
	y *= other;
	z *= other;
}

void Vec3::operator/=(float other){
	x /= other;
	y /= other;
	z /= other;
}

// Functions
Vec3 cross(const Vec3& a, const Vec3& b){
	return Vec3(
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	);
}

float dot(const Vec3& a, const Vec3& b){
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

float magnitude(const Vec3& a){
	return sqrt(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2));
}

float distance(const Vec3& a, const Vec3& b){
	return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2) + pow(b.z - a.z, 2));
}

Vec3 normalize(const Vec3& a){
	float m = magnitude(a);

	return Vec3(a.x / m, a.y / m, a.z / m);
}