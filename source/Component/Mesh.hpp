#pragma once

#include "Base\HelperComponent.hpp"

#include <GL\glew.h>
#include "Render\Cube.hpp"

#include "Transform.hpp"
#include "Phong.hpp"


class Mesh : public HelperComponent{
	Transform* _transform = 0;

public:
	Mesh(){

	}

	void load(){
		_transform = _getComponent<Transform>();
	}

	Component* clone(){
		return new Mesh;
	}

	void render(){
		glMatrixMode(GL_MODELVIEW);

		glPushMatrix();

		// Tranformations
		glTranslatef(_transform->position().x(), 0.f, 0.f);
		glTranslatef(0.f, _transform->position().y(), 0.f);
		glTranslatef(0.f, 0.f, _transform->position().z());

		glRotatef(_transform->euler().x(), 1.f, 0.f, 0.f);
		glRotatef(_transform->euler().y(), 0.f, 1.f, 0.f);
		glRotatef(_transform->euler().z(), 0.f, 0.f, 1.f);

		Phong* phong = _getComponent<Phong>();

		if (phong)
			phong->use();
		else
			glBindTexture(GL_TEXTURE_2D, 0);

		// Testing quad
		glBegin(GL_QUADS);

			glTexCoord2f(0.f, 1.f);
			glVertex3f(-1.0f, -1.0f, 0.0f);

			glTexCoord2f(0.f, 0.f);
			glVertex3f(-1.0f, 1.0f, 0.0f);

			glTexCoord2f(1.f, 0.f);
			glVertex3f(1.0f, 1.0f, 0.0f);

			glTexCoord2f(1.f, 1.f);
			glVertex3f(1.0f, -1.0f, 0.0f);

		glEnd();

		glPopMatrix();
	}
};