#include "mat4.hpp"

#define _USEmATH_DEFINES
#include <cmath>

// Methods
mat4::mat4(){
	// Identity matrix
	for (int y = 0; y < 4; y++){
		for (int x = 0; x < 4; x++){
			m[y][x] = 0.f;
		}
	}
	
	m[0][0] = 1.f;
	m[1][1] = 1.f;
	m[2][2] = 1.f;
	m[3][3] = 1.f;
}

mat4::mat4(const mat4& other){
	for (int y = 0; y < 4; y++){
		for (int x = 0; x < 4; x++){
			m[y][x] = other.m[y][x];
		}
	}
}

mat4::mat4(float a0, float a1, float a2, float a3, float b0, float b1, float b2, float b3, float c0, float c1, float c2, float c3, float d0, float d1, float d2, float d3){
	m[0][0] = a0; // x1
	m[0][1] = a1; // x2
	m[0][2] = a2; // x3
	m[0][3] = a3; // x4
						 			
	m[1][0] = b0; // y1
	m[1][1] = b1; // y2
	m[1][2] = b2; // y3
	m[1][3] = b3; // y4
						 					
	m[2][0] = c0; // z1
	m[2][1] = c1; // z2
	m[2][2] = c2; // z3
	m[2][3] = c3; // z4
						 		
	m[3][0] = d0; // w1
	m[3][1] = d1; // w2
	m[3][2] = d2; // w3
	m[3][3] = d3; // w4
}

void* mat4::gl(){
	return &m[0][0];
}

unsigned int mat4::length(){
	return 16;
}

mat4 mat4::operator*(const mat4& other){	
	return inverse(mat4(
		m[0][0] * other.m[0][0] + m[0][1] * other.m[1][0] + m[0][2] * other.m[2][0] + m[0][3] * other.m[3][0],
		m[0][0] * other.m[0][1] + m[0][1] * other.m[1][1] + m[0][2] + other.m[2][1] + m[0][3] * other.m[3][1],
		m[0][0] * other.m[0][2] + m[0][1] * other.m[1][2] + m[0][2] + other.m[2][2] + m[0][3] * other.m[3][2],
		m[0][0] * other.m[0][3] + m[0][1] * other.m[1][3] + m[0][2] + other.m[2][3] + m[0][3] * other.m[3][3],

		m[1][0] * other.m[0][0] + m[1][1] * other.m[1][0] + m[1][2] * other.m[2][0] + m[1][3] * other.m[3][0],
		m[1][0] * other.m[0][1] + m[1][1] * other.m[1][1] + m[1][2] + other.m[2][1] + m[1][3] * other.m[3][1],
		m[1][0] * other.m[0][2] + m[1][1] * other.m[1][2] + m[1][2] + other.m[2][2] + m[1][3] * other.m[3][2],
		m[1][0] * other.m[0][3] + m[1][1] * other.m[1][3] + m[1][2] + other.m[2][3] + m[1][3] * other.m[3][3],

		m[2][0] * other.m[0][0] + m[2][1] * other.m[1][0] + m[2][2] * other.m[2][0] + m[2][3] * other.m[3][0],
		m[2][0] * other.m[0][1] + m[2][1] * other.m[1][1] + m[2][2] + other.m[2][1] + m[2][3] * other.m[3][1],
		m[2][0] * other.m[0][2] + m[2][1] * other.m[1][2] + m[2][2] + other.m[2][2] + m[2][3] * other.m[3][2],
		m[2][0] * other.m[0][3] + m[2][1] * other.m[1][3] + m[2][2] + other.m[2][3] + m[2][3] * other.m[3][3],

		m[3][0] * other.m[0][0] + m[3][1] * other.m[1][0] + m[3][2] * other.m[2][0] + m[3][3] * other.m[3][0],
		m[3][0] * other.m[0][1] + m[3][1] * other.m[1][1] + m[3][2] + other.m[2][1] + m[3][3] * other.m[3][1],
		m[3][0] * other.m[0][2] + m[3][1] * other.m[1][2] + m[3][2] + other.m[2][2] + m[3][3] * other.m[3][2],
		m[3][0] * other.m[0][3] + m[3][1] * other.m[1][3] + m[3][2] + other.m[2][3] + m[3][3] * other.m[3][3]
	));
}

void mat4::operator*=(const mat4& other){
	(*this) = (*this) * other;
}

vec3 mat4::operator*(const vec3& other){
	vec3 transformed(
		m[0][0] * other.x + m[0][1] * other.y + m[0][2] * other.z + m[0][3] * 1.f,
		m[1][0] * other.x + m[1][1] * other.y + m[1][2] * other.z + m[1][3] * 1.f,
		m[2][0] * other.x + m[2][1] * other.y + m[2][2] * other.z + m[2][3] * 1.f
	);
	
	float w = m[3][0] * other.x + m[3][1] * other.y + m[3][2] * other.z + m[3][3] * 1.f;

	return transformed / w;
}

// Implementation for inverse modifed from GLU library http://www.mesa3d.org/

mat4 inverse(const mat4& a){
	float inv[16];

	inv[0] = a.m[1][1] * a.m[2][2] * a.m[3][3] -
			a.m[1][1] * a.m[2][3] * a.m[3][2] -
			a.m[2][1] * a.m[1][2] * a.m[3][3] +
			a.m[2][1] * a.m[1][3] * a.m[3][2] +
			a.m[3][1] * a.m[1][2] * a.m[2][3] -
			a.m[3][1] * a.m[1][3] * a.m[2][2];

	inv[4] = -a.m[1][0] * a.m[2][2] * a.m[3][3] +
		a.m[1][0] * a.m[2][3] * a.m[3][2] +
		a.m[2][0] * a.m[1][2] * a.m[3][3] -
		a.m[2][0] * a.m[1][3] * a.m[3][2] -
		a.m[3][0] * a.m[1][2] * a.m[2][3] +
		a.m[3][0] * a.m[1][3] * a.m[2][2];

	inv[8] = a.m[1][0] * a.m[2][1] * a.m[3][3] -
		a.m[1][0] * a.m[2][3] * a.m[3][1] -
		a.m[2][0] * a.m[1][1] * a.m[3][3] +
		a.m[2][0] * a.m[1][3] * a.m[3][1] +
		a.m[3][0] * a.m[1][1] * a.m[2][3] -
		a.m[3][0] * a.m[1][3] * a.m[2][1];

	inv[12] = -a.m[1][0] * a.m[2][1] * a.m[3][2] +
		a.m[1][0] * a.m[2][2] * a.m[3][1] +
		a.m[2][0] * a.m[1][1] * a.m[3][2] -
		a.m[2][0] * a.m[1][2] * a.m[3][1] -
		a.m[3][0] * a.m[1][1] * a.m[2][2] +
		a.m[3][0] * a.m[1][2] * a.m[2][1];

	inv[1] = -a.m[0][1] * a.m[2][2] * a.m[3][3] +
		a.m[0][1] * a.m[2][3] * a.m[3][2] +
		a.m[2][1] * a.m[0][2] * a.m[3][3] -
		a.m[2][1] * a.m[0][3] * a.m[3][2] -
		a.m[3][1] * a.m[0][2] * a.m[2][3] +
		a.m[3][1] * a.m[0][3] * a.m[2][2];

	inv[5] = a.m[0][0] * a.m[2][2] * a.m[3][3] -
		a.m[0][0] * a.m[2][3] * a.m[3][2] -
		a.m[2][0] * a.m[0][2] * a.m[3][3] +
		a.m[2][0] * a.m[0][3] * a.m[3][2] +
		a.m[3][0] * a.m[0][2] * a.m[2][3] -
		a.m[3][0] * a.m[0][3] * a.m[2][2];

	inv[9] = -a.m[0][0] * a.m[2][1] * a.m[3][3] +
		a.m[0][0] * a.m[2][3] * a.m[3][1] +
		a.m[2][0] * a.m[0][1] * a.m[3][3] -
		a.m[2][0] * a.m[0][3] * a.m[3][1] -
		a.m[3][0] * a.m[0][1] * a.m[2][3] +
		a.m[3][0] * a.m[0][3] * a.m[2][1];

	inv[13] = a.m[0][0] * a.m[2][1] * a.m[3][2] -
		a.m[0][0] * a.m[2][2] * a.m[3][1] -
		a.m[2][0] * a.m[0][1] * a.m[3][2] +
		a.m[2][0] * a.m[0][2] * a.m[3][1] +
		a.m[3][0] * a.m[0][1] * a.m[2][2] -
		a.m[3][0] * a.m[0][2] * a.m[2][1];

	inv[2] = a.m[0][1] * a.m[1][2] * a.m[3][3] -
		a.m[0][1] * a.m[1][3] * a.m[3][2] -
		a.m[1][1] * a.m[0][2] * a.m[3][3] +
		a.m[1][1] * a.m[0][3] * a.m[3][2] +
		a.m[3][1] * a.m[0][2] * a.m[1][3] -
		a.m[3][1] * a.m[0][3] * a.m[1][2];

	inv[6] = -a.m[0][0] * a.m[1][2] * a.m[3][3] +
		a.m[0][0] * a.m[1][3] * a.m[3][2] +
		a.m[1][0] * a.m[0][2] * a.m[3][3] -
		a.m[1][0] * a.m[0][3] * a.m[3][2] -
		a.m[3][0] * a.m[0][2] * a.m[1][3] +
		a.m[3][0] * a.m[0][3] * a.m[1][2];

	inv[10] = a.m[0][0] * a.m[1][1] * a.m[3][3] -
		a.m[0][0] * a.m[1][3] * a.m[3][1] -
		a.m[1][0] * a.m[0][1] * a.m[3][3] +
		a.m[1][0] * a.m[0][3] * a.m[3][1] +
		a.m[3][0] * a.m[0][1] * a.m[1][3] -
		a.m[3][0] * a.m[0][3] * a.m[1][1];

	inv[14] = -a.m[0][0] * a.m[1][1] * a.m[3][2] +
		a.m[0][0] * a.m[1][2] * a.m[3][1] +
		a.m[1][0] * a.m[0][1] * a.m[3][2] -
		a.m[1][0] * a.m[0][2] * a.m[3][1] -
		a.m[3][0] * a.m[0][1] * a.m[1][2] +
		a.m[3][0] * a.m[0][2] * a.m[1][1];

	inv[3] = -a.m[0][1] * a.m[1][2] * a.m[2][3] +
		a.m[0][1] * a.m[1][3] * a.m[2][2] +
		a.m[1][1] * a.m[0][2] * a.m[2][3] -
		a.m[1][1] * a.m[0][3] * a.m[2][2] -
		a.m[2][1] * a.m[0][2] * a.m[1][3] +
		a.m[2][1] * a.m[0][3] * a.m[1][2];

	inv[7] = a.m[0][0] * a.m[1][2] * a.m[2][3] -
		a.m[0][0] * a.m[1][3] * a.m[2][2] -
		a.m[1][0] * a.m[0][2] * a.m[2][3] +
		a.m[1][0] * a.m[0][3] * a.m[2][2] +
		a.m[2][0] * a.m[0][2] * a.m[1][3] -
		a.m[2][0] * a.m[0][3] * a.m[1][2];

	inv[11] = -a.m[0][0] * a.m[1][1] * a.m[2][3] +
		a.m[0][0] * a.m[1][3] * a.m[2][1] +
		a.m[1][0] * a.m[0][1] * a.m[2][3] -
		a.m[1][0] * a.m[0][3] * a.m[2][1] -
		a.m[2][0] * a.m[0][1] * a.m[1][3] +
		a.m[2][0] * a.m[0][3] * a.m[1][1];

	inv[15] = a.m[0][0] * a.m[1][1] * a.m[2][2] -
		a.m[0][0] * a.m[1][2] * a.m[2][1] -
		a.m[1][0] * a.m[0][1] * a.m[2][2] +
		a.m[1][0] * a.m[0][2] * a.m[2][1] +
		a.m[2][0] * a.m[0][1] * a.m[1][2] -
		a.m[2][0] * a.m[0][2] * a.m[1][1];

	float det = a.m[0][0] * inv[0] + a.m[0][1] * inv[4] + a.m[0][2] * inv[8] + a.m[0][3] * inv[12];

	if (det == 0)
		return mat4();

	det = 1.0 / det;

	return mat4(
		inv[0] * det, inv[1] * det, inv[2] * det, inv[3] * det,
		inv[4] * det, inv[5] * det, inv[6] * det, inv[7] * det,
		inv[8] * det, inv[9] * det, inv[10] * det, inv[11] * det,
		inv[12] * det, inv[13] * det, inv[14] * det, inv[15] * det
	);
}

mat4 mat4Cast(const quat& a){
	quat i = inverse(a);

	return mat4(
		1.f - 2.f * pow(i.y, 2) - 2.f * pow(i.z, 2),
		2.f * i.x * i.y - 2.f * i.z * i.w,
		2.f * i.x * i.z + 2.f * i.y * i.w,
		0.f,

		2.f * i.x * i.y + 2.f * i.z * i.w,
		1.f - 2.f * pow(i.x, 2) - 2.f * pow(i.z, 2),
		2.f * i.y * i.z - 2.f * i.x * i.w,
		0.f,

		2.f * i.x * i.z - 2.f * i.y * i.w,
		2.f * i.y * i.z + 2.f * i.x * i.w,
		1.f - 2.f * pow(i.x, 2) - 2.f * pow(i.y, 2),
		0.f,

		0.f,
		0.f,
		0.f,
		1.f
	);
}