#pragma once

#include "Helper.hpp"

#include <GL\glew.h>
//#include <SDL_image.h>

//#include "Render\Teapot.hpp"

#include "Component\Transform.hpp"

class Mesh : public HelperComponent{
	Transform* transform = 0;

	//GLuint _texture = -1;	

public:
	Mesh(){}

	void load(){
		/*
		// Texture testing

		SDL_Surface* image = IMG_Load("../asset/bort.png");

		glGenTextures(1, &_texture);
		glBindTexture(GL_TEXTURE_2D, _texture);

		int format = GL_RGB;

		if (image->format->BytesPerPixel == 4)
			format = GL_RGBA;

		glTexImage2D(GL_TEXTURE_2D, 0, format, image->w, image->h, 0, format, GL_UNSIGNED_BYTE, image->pixels);

		SDL_FreeSurface(image);*/

		transform = getComponent<Transform>();
	}

	Component* clone(){
		return new Mesh;
	}

	void update(long dt){
		transform->translate(Vector3f(0.f, 0.f, -0.02f));
		transform->transform(Vector3f(0.5f, 1.f, 2.f));
	}

	void render(){
		glPushMatrix();

		glTranslatef(transform->position().x(), transform->position().y(), transform->position().z());

		glRotatef(transform->euler().x(), 1.f, 0.f, 0.f);
		glRotatef(transform->euler().y(), 0.f, 1.f, 0.f);
		glRotatef(transform->euler().z(), 0.f, 0.f, 1.f);

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