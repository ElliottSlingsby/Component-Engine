#pragma once

#include "Mesh.hpp"

// Derives from mesh, and overrides render.
// This will be deleted when the obj loader is finished.

class Floor : public Mesh{
public:
	void render(){
		glMatrixMode(GL_MODELVIEW);

		glPushMatrix();

		Material* material = _getComponent<Material>();

		if (material)
			material->use();
		else
			glBindTexture(GL_TEXTURE_2D, 0);

		glTranslatef(0.f, _transform->position().y(), 0.f);

		glScalef(50.f, 50.f, 50.f);

		glBegin(GL_QUADS);

		glNormal3f(0.f, -1.f, 0.f);
		
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

	Component* clone(){
		return new Mesh;
	}
};