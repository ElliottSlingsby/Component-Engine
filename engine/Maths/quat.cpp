#include "quat.hpp"

#define _USE_MATH_DEFINES
#include <cmath>

// Methods
quat::quat(){}

quat::quat(float w, float x, float y, float z){
	this->w = w;
	this->x = x;
	this->y = y;
	this->z = z;
}

quat::quat(const vec3& angles){
	float a1 = cos(angles.y / 2.f);
	float a2 = cos(angles.z / 2.f);
	float a3 = cos(angles.x / 2.f);
	
	float b1 = sin(angles.y / 2.f);
	float b2 = sin(angles.z / 2.f);
	float b3 = sin(angles.x / 2.f);
	
	//w = a1 * a2 * a3 - b1 * b2 * b3;
	//z = b1 * b2 * a3 + a1 * a2 * b3;
	//y = b1 * a2 * a3 + a1 * b2 * b3;
	//x = a1 * b2 * a3 - b1 * a2 * b3;

	w = a1 * a2 * a3 - b1 * b2 * b3;
	x = -(b1 * b2 * a3 - a1 * a2 * b3);
	y = b1 * a2 * a3 + a1 * b2 * b3;
	z = a1 * b2 * a3 - b1 * a2 * b3;
}

void quat::operator=(const quat& other){
	x = other.x;
	y = other.y;
	z = other.z;
	w = other.w;
}

quat quat::operator*(const quat& other){
	return quat(
		other.w * w - other.y * y - other.z * z - other.x * x,
		other.w * x - other.y * z + other.z * y + other.x * w,
		other.w * y + other.y * w - other.z * x + other.x * z,
		other.w * z + other.y * x + other.z * w - other.x * y
	);
}

void quat::operator*=(const quat& other){
	(*this) = (*this) * other;
}

vec3 quat::operator*(const vec3& other){
	//quat converted(other.x, other.y, other.z, 0.f);
	return vec3();
}

// Functions
quat conjugate(const quat& a){
	return quat(a.w, -a.x, -a.y, -a.z);
}

vec3 eulerAngles(const quat& a){
	//float x  = atan((2 * (a.w * a.x + a.y * a.z)) / (pow(a.w, 2) - pow(a.x, 2) - pow(a.y, 2) + pow(a.z, 2)));
	//
	//float y = -asin(2 * (a.x * a.z - a.w * a.y));
	//
	//float z = atan((2 * (a.w * a.z + a.x * a.y)) / (pow(a.w, 2) - pow(a.x, 2) - pow(a.y, 2) + pow(a.z, 2)));
	//
	//return vec3(x, y, z);



	float x = atan2f(2 * (a.w * a.x + a.y * a.z), 1 - 2 * (pow(a.x, 2) + pow(a.y, 2)));
	float y = asin(2 * (a.w * a.y - a.z * a.x));
	float z = atan2(2 * (a.w * a.z + a.x * a.y), 1 - 2 * (pow(a.y, 2) + pow(a.z, 2)));

	//float x = atan2f(2 * (q0 * q1 + q2 * q3), 1 - 2 * (pow(q1, 2) + pow(q2, 2)));
	//float y = asin(2 * (q0 * q2 - q3 * q1));
	//float z = atan2(2 * (q0 * q3 + q1 * q2), 1 - 2(pow(q2, 2) + pow(q3, 2)));







	return vec3(x, y, z);







	//float y = atan2(2 * a.y * a.w - 2 * a.x * a.z, 1 - 2 * pow(a.y, 2) - 2 * pow(a.z, 2));
	//float x = asin(2 * a.x * a.y + 2 * a.z * a.w);
	//float z = atan2(2 * a.x * a.w - 2 * a.y * a.z, 1 - 2 * pow(a.x, 2) - 2 * pow(a.z, 2));
	//
	//if (a.x * a.y + a.z * a.w == 0.f)

	




	//float x  = atan((2 * (a * b + c * d)) / (pow(a, 2) - pow(b, 2) - pow(c, 2) + pow(d, 2)));
	//
	//float y = asin(2 * (b * d - a * c));
	//
	//float z = atan((2 * (a * d + b * c)) / (pow(a, 2) - pow(b, 2) - pow(c, 2) + pow(d, 2)));
}

quat inverse(const quat& a){
	return quat();
}

float magnitude(const quat& a){
	return sqrt(pow(a.w, 2) + pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2));
}

quat normalize(const quat& a){
	float m = magnitude(a);

	return quat(a.w / m, a.x / m, a.y / m, a.z / m);
}