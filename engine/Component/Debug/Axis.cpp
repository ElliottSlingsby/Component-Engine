#include "Axis.hpp"

#include <GL\glew.h>

Axis::Axis(float length, bool fixedRotation){
	_length = length;
	
	setUnlit(true);
	setFixedRotation(fixedRotation);
}

void Axis::draw(){
	glLineWidth(2);

	glBegin(GL_LINES);

	glColor3f(1.f, 0.f, 0.f);
	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(_length, 0.f, 0.f);

	glColor3f(0.f, 1.f, 0.f);
	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(0.f, _length, 0.f);

	glColor3f(0.f, 0.f, 1.f);
	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(0.f, 0.f, _length);

	glColor3f(1.f, 1.f, 1.f);

	glEnd();

	glLineWidth(1);
}