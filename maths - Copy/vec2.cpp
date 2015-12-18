#include "vec2.hpp"

#define _USE_MATH_DEFINES
#include <cmath>

// Methods
vec2::vec2(){}

vec2::vec2(const vec2& other){
	this->x = other.x;
	this->y = other.y;
}

vec2::vec2(float x, float y){
	this->x = x;
	this->y = y;
}

unsigned int vec2::length(){
	return 2;
}

void* vec2::gl(){
	float values[2] = { x, y };
	return values;
}

void vec2::operator=(const vec2& other){
	x = other.x;
	y = other.y;
}

vec2 vec2::operator+(const vec2& other){
	return vec2(x + other.x, y + other.y);
}

vec2 vec2::operator-(const vec2& other){
	return vec2(x - other.x, y - other.y);
}

vec2 vec2::operator*(const vec2& other){
	return vec2(x * other.x, y * other.y);
}

vec2 vec2::operator/(const vec2& other){
	return vec2(x / other.x, y / other.y);
}

void vec2::operator+=(const vec2& other){
	x += other.x;
	y += other.y;
}

void vec2::operator-=(const vec2& other){
	x -= other.x;
	y -= other.y;
}

void vec2::operator*=(const vec2& other){
	x *= other.x;
	y *= other.y;
}

void vec2::operator/=(const vec2& other){
	x /= other.x;
	y /= other.y;
}

vec2 vec2::operator+(float other){
	return vec2(x + other, y + other);
}

vec2 vec2::operator-(float other){
	return vec2(x - other, y - other);
}

vec2 vec2::operator*(float other){
	return vec2(x * other, y * other);
}

vec2 vec2::operator/(float other){
	return vec2(x / other, y / other);
}

void vec2::operator+=(float other){
	x += other;
	y += other;
}

void vec2::operator-=(float other){
	x -= other;
	y -= other;
}


void vec2::operator*=(float other){
	x *= other;
	y *= other;
}

void vec2::operator/=(float other){
	x /= other;
	y /= other;
}

// Functions
float dot(const vec2& a, const vec2& b){
	return a.x * b.x + a.y * b.y;
}

float magnitude(const vec2& a){
	return sqrt(pow(a.x, 2) + pow(a.y, 2));
}

float distance(const vec2& a, const vec2& b){
	return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

vec2 normalize(const vec2& a){
	float m = magnitude(a);

	return vec2(a.x / m, a.y / m);
}