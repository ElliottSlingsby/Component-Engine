#pragma once

#include "Base.hpp"

#include <SDL_opengl.h>

#include "Render\Teapot.hpp"

#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtx/transform.hpp>

#include "Render\Window.hpp"

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
		distance -= 0.5f;
	}

	void render(){
		glPushMatrix();

		glTranslatef(0.f, 0.f, distance);

		glBegin(GL_TRIANGLES);
			glVertex3f(0.0f, 1.0f, 0.0f);
			glVertex3f(-1.0f, -1.0f, 0.0f);
			glVertex3f(1.0f, -1.0f, 0.0f);
		glEnd();
		
		glPopMatrix();


		//glm::mat4 view = translate(glm::vec3(0.f, 0.f, 100.f));


		/*glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, teapot_vertices);
		glTranslatef(0.f, 0.f, -5.f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, teapot_body);

		glDisableClientState(GL_VERTEX_ARRAY);*/
	}
};