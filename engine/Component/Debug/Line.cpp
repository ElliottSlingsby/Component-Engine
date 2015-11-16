#include "Line.hpp"

Line::Line(const glm::vec3& vector){
	setVector(vector);
	setUnlit(true);
}

void Line::setVector(const glm::vec3& vector){
	_vector = vector;
}

glm::vec3 Line::vector(){
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