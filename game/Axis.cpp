#include "Axis.hpp"

#include <GL\glew.h>

Axis::Axis(float length, bool local){
	_length = length;
	_local = local;
}

void Axis::load(){
	_transform = getComponent<Transform>();
}

void Axis::render(){
	glPushMatrix();

	bool switched = false;

	if (glIsEnabled(GL_LIGHTING)){
		glDisable(GL_LIGHTING);
		switched = true;
	}

	glTranslatef(-_transform->position().x, -_transform->position().y, -_transform->position().z);

	if (_local)
		glMultMatrixf(&glm::mat4_cast(_transform->rotation())[0][0]);

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
	
	if (switched)
		glEnable(GL_LIGHTING);

	glPopMatrix();
}