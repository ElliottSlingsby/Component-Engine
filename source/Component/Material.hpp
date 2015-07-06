#pragma once

#include "Base\HelperComponent.hpp"
#include "AssetLoader.hpp"
#include <GL\glew.h>

class Material : public HelperComponent{
	//GLuint _ambient = -1;
	//std::string _ambient_src;

	GLuint _diffuse = -1;
	std::string _diffuse_src;

	//GLuint _specular = -1;
	//std::string _specular_src;

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
		_diffuse = AssetLoader::getAsset(_diffuse_src);
	}

	void use(){
		glBindTexture(GL_TEXTURE_2D, _diffuse);
	}
};