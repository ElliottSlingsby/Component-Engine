#pragma once

#include "Base.hpp"

#include <SDL_opengl.h>

#include "Render\Teapot.hpp"

class Mesh : public Component{
	float distance = 0;

public:
	Mesh(){

	}

	Component* clone(){
		return new Mesh;
	}

	void load(){

	}

	void update(long dt){
		distance -= 0.01f;
	}

	void render(){
		glPushMatrix();

		glTranslatef(0.f, 0.f, distance);

		glRotatef(distance * 100, 1.f, 1.f, 1.f);

		glBegin(GL_TRIANGLES);
			glColor3f(1.f, 0.f, 0.f);
			glVertex3f(0.0f, 1.0f, 0.0f);
			glColor3f(0.f, 1.f, 0.f);
			glVertex3f(-1.0f, -1.0f, 0.0f);
			glColor3f(0.f, 0.f, 1.f);
			glVertex3f(1.0f, -1.0f, 0.0f);
		glEnd();
		
		glPopMatrix();
	}
};