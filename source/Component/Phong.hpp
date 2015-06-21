#pragma once

#include "Helper.hpp"

#include <SDL_image.h>

class Phong : public HelperComponent{
	Transform* _transform = 0;
	//GLuint _texture = -1;	

public:
	Phong(){

	}

	Component* clone(){
		return new Phong;
	}

	void load(){
		_transform = _getComponent<Transform>();

		/*// Texture testing

		SDL_Surface* image = IMG_Load("../asset/bort.png");

		glGenTextures(1, &_texture);
		glBindTexture(GL_TEXTURE_2D, _texture);

		int format = GL_RGB;

		if (image->format->BytesPerPixel == 4)
		format = GL_RGBA;

		glTexImage2D(GL_TEXTURE_2D, 0, format, image->w, image->h, 0, format, GL_UNSIGNED_BYTE, image->pixels);

		SDL_FreeSurface(image);*/
	}
};