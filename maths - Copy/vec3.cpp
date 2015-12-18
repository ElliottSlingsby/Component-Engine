#include "vec3.hpp"

#define _USE_MATH_DEFINES
#include <cmath>

// Methods
vec3::vec3(){}

vec3::vec3(const vec3& other){
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
}

vec3::vec3(float x, float y, float z){
	this->x = x;
	this->y = y;
	this->z = z;
}

unsigned int length(){
	return 3;
}

void* vec3::gl(){
	float values[3] = { x, y, z };
	return values;
}

void vec3::operator=(const vec3& other){
	x = other.x;
	y = other.y;
	z = other.z;
}

vec3 vec3::operator+(const vec3& other){
	return vec3(x + other.x, y + other.y, z + other.z);
}

vec3 vec3::operator-(const vec3& other){
	return vec3(x - other.x, y - other.y, z - other.z);
}

vec3 vec3::operator*(const vec3& other){
	return vec3(x * other.x, y * other.y, z * other.z);
}

vec3 vec3::operator/(const vec3& other){
	return vec3(x / other.x, y / other.y, z / other.z);
}

void vec3::operator+=(const vec3& other){
	x += other.x;
	y += other.y;
	z += other.z;
}

void vec3::operator-=(const vec3& other){
	x -= other.x;
	y -= other.y;
	z -= other.z;
}

void vec3::operator*=(const vec3& other){
	x *= other.x;
	y *= other.y;
	z *= other.z;
}
void vec3::operator/=(const vec3& other){
	x /= other.x;
	y /= other.y;
	z /= other.z;
}

vec3 vec3::operator+(float other){
	return vec3(x + other, y + other, z + other);
}

vec3 vec3::operator-(float other){
	return vec3(x - other, y - other, z - other);
}

vec3 vec3::operator*(float other){
	return vec3(x * other, y * other, z * other);
}

vec3 vec3::operator/(float other){
	return vec3(x / other, y / other, z / other);
}

void vec3::operator+=(float other){
	x += other;
	y += other;
	z += other;
}

void vec3::operator-=(float other){
	x -= other;
	y -= other;
	z -= other;
}


void vec3::operator*=(float other){
	x *= other;
	y *= other;
	z *= other;
}

void vec3::operator/=(float other){
	x /= other;
	y /= other;
	z /= other;
}

// Functions
vec3 cross(const vec3& a, const vec3& b){
	return vec3(
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	);
}

float dot(const vec3& a, const vec3& b){
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

float magnitude(const vec3& a){
	return sqrt(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2));
}

float distance(const vec3& a, const vec3& b){
	return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2) + pow(b.z - a.z, 2));
}

vec3 normalize(const vec3& a){
	float m = magnitude(a);

	return vec3(a.x / m, a.y / m, a.z / m);
}