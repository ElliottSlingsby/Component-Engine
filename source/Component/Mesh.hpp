#pragma once

#include "Helper.hpp"

#include <GL\glew.h>

#include "Component\Transform.hpp"

class Mesh : public HelperComponent{
	Transform* _transform = 0;

public:
	Mesh(){}

	void load(){
		_transform = getComponent<Transform>();
	}

	Component* clone(){
		return new Mesh;
	}

	void render(){
		glPushMatrix();

		// Transform tranformations
		glTranslatef(_transform->position().x(), 0.f, 0.f);
		glTranslatef(0.f, _transform->position().y(), 0.f);
		glTranslatef(0.f, 0.f, _transform->position().z());

		glRotatef(_transform->euler().x(), 1.f, 0.f, 0.f);
		glRotatef(_transform->euler().y(), 0.f, 1.f, 0.f);
		glRotatef(_transform->euler().z(), 0.f, 0.f, 1.f);

		// Testing quad
		glBegin(GL_QUADS);

			glColor3f(1.f, 0.f, 0.f);
			glTexCoord2f(0.f, 0.f);
			glVertex3f(-1.0f, -1.0f, 0.0f);

			glColor3f(0.f, 1.f, 0.f);
			glTexCoord2f(0.f, 1.f);
			glVertex3f(-1.0f, 1.0f, 0.0f);

			glColor3f(0.f, 0.f, 1.f);
			glTexCoord2f(1.f, 1.f);
			glVertex3f(1.0f, 1.0f, 0.0f);

			glColor3f(1.f, 1.f, 1.f);
			glTexCoord2f(1.f, 0.f);
			glVertex3f(1.0f, -1.0f, 0.0f);

		glEnd();

		glPopMatrix();
	}
};