#include "Line.hpp"

Line::Line(const Vec3& vector){
	setVector(vector);
	setUnlit(true);
}

void Line::setVector(const Vec3& vector){
	_vector = vector;
}

Vec3 Line::vector(){
	return _vector;
}

void Line::draw(){
	glLineWidth(3);

	glBegin(GL_LINES);

	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(_vector.x, _vector.y, _vector.z);

	glEnd();

	glLineWidth(1);
}