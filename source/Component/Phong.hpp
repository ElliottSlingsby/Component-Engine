#pragma once

#include "Helper.hpp"

#include <string>
#include <SDL_image.h>

class Phong : public HelperComponent{
	GLuint _texture = -1;
	std::string _image;

public:
	Phong(std::string image){
		_image = image;
	}

	Component* clone(){
		return new Phong(_image);
	}

	void load(){
		SDL_Surface* image = IMG_Load(("../asset/" + _image).c_str());

		if (!image){
			printf("%s %s!", "Cannot load texture", _image);
			return;
		}

		glGenTextures(1, &_texture);
		glBindTexture(GL_TEXTURE_2D, _texture);

		int format = GL_RGB;

		if (image->format->BytesPerPixel == 4)
			format = GL_RGBA;

		glTexImage2D(GL_TEXTURE_2D, 0, format, image->w, image->h, 0, format, GL_UNSIGNED_BYTE, image->pixels);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		SDL_FreeSurface(image);
	}

	void use(){
		glBindTexture(GL_TEXTURE_2D, _texture);
	}
};