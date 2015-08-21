#pragma once

#include "Model.hpp"

// Derives from mesh, and overrides render.
// This will be deleted when the obj loader is finished.

class Floor : public Model{
public:
	Floor(std::string materialSrc = "") : Model("", materialSrc){}

	void render(){
		glMatrixMode(GL_MODELVIEW);

		glPushMatrix();

		if (_material)
			glBindTexture(GL_TEXTURE_2D, _material->diffuse);
		else
			glBindTexture(GL_TEXTURE_2D, 0);

		glTranslatef(0.f, _transform->position().y(), 0.f);

		glScalef(50.f, 50.f, 50.f);

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

		glPopMatrix();
	}
};