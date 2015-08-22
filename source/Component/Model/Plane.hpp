#pragma once

#include "Model.hpp"

class Plane : public Model{
public:
	Plane(std::string materialSrc = "") : Model("", materialSrc){}

	void draw(){
		glBegin(GL_QUADS);

		glNormal3f(0.f, 1.f, 0.f);
		
		glTexCoord2f(1.f, 1.f);
		glVertex3f(-1.f, 0.f, 1.f);
		glTexCoord2f(1.f, 0.f);
		glVertex3f(1.f, 0.f, 1.f);
		glTexCoord2f(0.f, 0.f);
		glVertex3f(1.f, 0.f, -1.f);
		glTexCoord2f(0.f, 1.f);
		glVertex3f(-1.f, 0.f, -1.f);

		glEnd();
	}
};