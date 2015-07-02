#pragma once

#include "Base\HelperComponent.hpp"

#include <string>
#include <SDL_image.h>
#include <GL\glew.h>

#include "ResourceLoader.hpp"

class Material : public HelperComponent{
	GLuint _ambient = -1;
	std::string _ambient_src;

	GLuint _diffuse = -1;
	std::string _diffuse_src;

	GLuint _specular = -1;
	std::string _specular_src;

public:
	Material(std::string image){
		_diffuse_src = image;
	}

	~Material(){
		glDeleteTextures(1, &_diffuse);
	}

	Component* clone(){
		return new Material(_diffuse_src);
	}

	void load(){
		_diffuse = ResourceLoader::getResource("regressiontest.jpg");
	}

	void use(){
		glBindTexture(GL_TEXTURE_2D, _diffuse);
	}
};