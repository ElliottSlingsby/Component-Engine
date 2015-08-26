#pragma once

#include "Model.hpp"

class Cube : public Model{
public:
	Cube(std::string materialSrc = "") : Model("", materialSrc){}

	void draw(){
		glBegin(GL_QUADS);

		//Top
		glNormal3f(0.f, 1.f, 0.f);
		glTexCoord2f(1.f, 1.f);	glVertex3f(-1.f, 1.f, 1.f);
		glTexCoord2f(1.f, 0.f);	glVertex3f(1.f, 1.f, 1.f);
		glTexCoord2f(0.f, 0.f);	glVertex3f(1.f, 1.f, -1.f);
		glTexCoord2f(0.f, 1.f);	glVertex3f(-1.f, 1.f, -1.f);

		//Bottom
		glNormal3f(0.f, -1.f, 0.f);
		glTexCoord2f(0.f, 1.f);	glVertex3f(-1.f, -1.f, -1.f);
		glTexCoord2f(0.f, 0.f);	glVertex3f(1.f, -1.f, -1.f);
		glTexCoord2f(1.f, 0.f);	glVertex3f(1.f, -1.f, 1.f);
		glTexCoord2f(1.f, 1.f);	glVertex3f(-1.f, -1.f, 1.f);

		//Front
		glNormal3f(0.f, 0.f, 1.f);
		glTexCoord2f(1.f, 1.f);	glVertex3f(-1.f, -1.f, 1.f);
		glTexCoord2f(1.f, 0.f);	glVertex3f(1.f, -1.f, 1.f);
		glTexCoord2f(0.f, 0.f);	glVertex3f(1.f, 1.f, 1.f);
		glTexCoord2f(0.f, 1.f);	glVertex3f(-1.f, 1.f, 1.f);

		//Back
		glNormal3f(0.f, 0.f, -1.f);
		glTexCoord2f(0.f, 1.f);	glVertex3f(-1.f, 1.f, -1.f);
		glTexCoord2f(0.f, 0.f);	glVertex3f(1.f, 1.f, -1.f);
		glTexCoord2f(1.f, 0.f);	glVertex3f(1.f, -1.f, -1.f);
		glTexCoord2f(1.f, 1.f);	glVertex3f(-1.f, -1.f, -1.f);

		//Left
		glNormal3f(-1.f, 0.f, 0.f);
		glTexCoord2f(1.f, 1.f);	glVertex3f(-1.f, -1.f, -1.f);
		glTexCoord2f(1.f, 0.f);	glVertex3f(-1.f, -1.f, 1.f);
		glTexCoord2f(0.f, 0.f);	glVertex3f(-1.f, 1.f, 1.f);
		glTexCoord2f(0.f, 1.f);	glVertex3f(-1.f, 1.f, -1.f);

		//Right
		glNormal3f(1.f, 0.f, 0.f);
		glTexCoord2f(0.f, 1.f);	glVertex3f(1.f, 1.f, -1.f);
		glTexCoord2f(0.f, 0.f);	glVertex3f(1.f, 1.f, 1.f);
		glTexCoord2f(1.f, 0.f);	glVertex3f(1.f, -1.f, 1.f);
		glTexCoord2f(1.f, 1.f);	glVertex3f(1.f, -1.f, -1.f);

		glEnd();
	}
};