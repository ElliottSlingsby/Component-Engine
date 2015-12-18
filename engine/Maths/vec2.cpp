#include "Vec2.hpp"

#define _USE_MATH_DEFINES
#include <cmath>

// Methods
Vec2::Vec2(){}

Vec2::Vec2(const Vec2& other){
	this->x = other.x;
	this->y = other.y;
}

Vec2::Vec2(float x, float y){
	this->x = x;
	this->y = y;
}

unsigned int Vec2::length(){
	return 2;
}

void Vec2::operator=(const Vec2& other){
	x = other.x;
	y = other.y;
}

Vec2 Vec2::operator+(const Vec2& other){
	return Vec2(x + other.x, y + other.y);
}

Vec2 Vec2::operator-(const Vec2& other){
	return Vec2(x - other.x, y - other.y);
}

Vec2 Vec2::operator*(const Vec2& other){
	return Vec2(x * other.x, y * other.y);
}

Vec2 Vec2::operator/(const Vec2& other){
	return Vec2(x / other.x, y / other.y);
}

void Vec2::operator+=(const Vec2& other){
	x += other.x;
	y += other.y;
}

void Vec2::operator-=(const Vec2& other){
	x -= other.x;
	y -= other.y;
}

void Vec2::operator*=(const Vec2& other){
	x *= other.x;
	y *= other.y;
}

void Vec2::operator/=(const Vec2& other){
	x /= other.x;
	y /= other.y;
}

Vec2 Vec2::operator+(float other){
	return Vec2(x + other, y + other);
}

Vec2 Vec2::operator-(float other){
	return Vec2(x - other, y - other);
}

Vec2 Vec2::operator*(float other){
	return Vec2(x * other, y * other);
}

Vec2 Vec2::operator/(float other){
	return Vec2(x / other, y / other);
}

void Vec2::operator+=(float other){
	x += other;
	y += other;
}

void Vec2::operator-=(float other){
	x -= other;
	y -= other;
}


void Vec2::operator*=(float other){
	x *= other;
	y *= other;
}

void Vec2::operator/=(float other){
	x /= other;
	y /= other;
}

// Functions
float dot(const Vec2& a, const Vec2& b){
	return a.x * b.x + a.y * b.y;
}

float magnitude(const Vec2& a){
	return sqrt(pow(a.x, 2) + pow(a.y, 2));
}

float distance(const Vec2& a, const Vec2& b){
	return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

Vec2 normalize(const Vec2& a){
	float m = magnitude(a);

	return Vec2(a.x / m, a.y / m);
}