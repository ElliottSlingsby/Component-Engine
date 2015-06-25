#pragma once

#include "Base\HelperComponent.hpp"

#include <string>
#include <SDL_image.h>

class Phong : public HelperComponent{
	GLuint _ambient = -1;
	std::string _ambient_src;

	GLuint _diffuse = -1;
	std::string _diffuse_src;

	GLuint _specular = -1;
	std::string _specular_src;

public:
	Phong(std::string image){
		_diffuse_src = image;
	}

	~Phong(){
		glDeleteTextures(1, &_diffuse);
	}

	Component* clone(){
		return new Phong(_diffuse_src);
	}

	void load(){
		SDL_Surface* image = IMG_Load(("../asset/" + _diffuse_src).c_str());

		if (!image){
			printf("%s %s!", "Cannot load texture", _diffuse_src);
			return;
		}

		glGenTextures(1, &_diffuse);
		glBindTexture(GL_TEXTURE_2D, _diffuse);

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
		glBindTexture(GL_TEXTURE_2D, _diffuse);
	}
};