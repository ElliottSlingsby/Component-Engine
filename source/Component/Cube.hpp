#pragma once

#include "Model.hpp"

// Derives from mesh, and overrides render.
// This will be deleted when the obj loader is finished.

class Cube : public Model{
public:
	Cube(std::string materialSrc = "") : Model("", materialSrc){}

	void render(){
		glMatrixMode(GL_MODELVIEW);

		glPushMatrix();

		// Translate based on Transform
		glTranslatef(_transform->position().x(), 0.f, 0.f);
		glTranslatef(0.f, _transform->position().y(), 0.f);
		glTranslatef(0.f, 0.f, _transform->position().z());

		// Rotate based on Transform
		glRotatef(_transform->rotation().x(), 1.f, 0.f, 0.f);
		glRotatef(_transform->rotation().y(), 0.f, 1.f, 0.f);
		glRotatef(_transform->rotation().z(), 0.f, 0.f, 1.f);

		if (_material)
			glBindTexture(GL_TEXTURE_2D, _material->diffuse);
		else
			glBindTexture(GL_TEXTURE_2D, 0);

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

		glPopMatrix();
	}
};